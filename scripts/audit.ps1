$ErrorActionPreference = 'Stop'

$root = Resolve-Path (Join-Path $PSScriptRoot '..')
$rootPath = $root.Path
Set-Location $root

$errors = New-Object System.Collections.Generic.List[string]
$warnings = New-Object System.Collections.Generic.List[string]

function Add-Error($message) {
    $errors.Add($message) | Out-Null
}

function Add-Warning($message) {
    $warnings.Add($message) | Out-Null
}

function Get-RelativePath($path) {
    return $path.Substring($rootPath.Length + 1)
}

Write-Host '== Markdown code fences =='
$codeFence = ([string][char]96) * 3
Get-ChildItem -Recurse -Filter *.md | ForEach-Object {
    $text = Get-Content -Raw -Encoding UTF8 -LiteralPath $_.FullName
    $count = ([regex]::Matches($text, [regex]::Escape($codeFence))).Count
    if ($count % 2 -ne 0) {
        $relativeMd = Get-RelativePath $_.FullName
        Add-Error ("Unclosed code fence: {0}" -f $relativeMd)
    }
}

Write-Host '== Markdown local links =='
Get-ChildItem -Recurse -Filter *.md | ForEach-Object {
    $md = $_
    $base = Split-Path $md.FullName -Parent
    $text = Get-Content -Raw -Encoding UTF8 -LiteralPath $md.FullName
    foreach ($match in [regex]::Matches($text, '\[[^\]]+\]\(([^)]+)\)')) {
        $target = $match.Groups[1].Value.Trim()
        if ($target -match '^(https?:|mailto:|#)') { continue }

        $target = ($target -split '#')[0]
        if ([string]::IsNullOrWhiteSpace($target)) { continue }

        $target = $target.Trim('<', '>')
        try {
            $decoded = [uri]::UnescapeDataString($target)
        } catch {
            $decoded = $target
        }

        $full = Join-Path $base $decoded
        if (-not (Test-Path -LiteralPath $full)) {
            $relativeMd = Get-RelativePath $md.FullName
            Add-Error ("Broken link in {0}: {1}" -f $relativeMd, $target)
        }
    }
}

Write-Host '== Course directory counts =='
$courseDirs = Get-ChildItem -Directory | Where-Object { $_.Name -match '^0[1-9] ' }
$courseCount = 0
foreach ($semester in $courseDirs) {
    $courseCount += (Get-ChildItem -LiteralPath $semester.FullName -Directory).Count
}
if ($courseCount -ne 82) {
    Add-Error ("Expected 82 course directories in 01-09, found {0}" -f $courseCount)
}

Write-Host '== Exam archive counts =='
$examRootItem = Get-ChildItem -Directory | Where-Object { $_.Name -like '10 *' } | Select-Object -First 1
if (-not $examRootItem) {
    Add-Error 'Missing exam archive directory with prefix 10.'
    $examRoot = $null
} else {
    $examRoot = $examRootItem.FullName
}
if ($examRoot) {
    $examDirs = (Get-ChildItem -LiteralPath $examRoot -Directory).Count
    $examDocs = (Get-ChildItem -LiteralPath $examRoot -Recurse -File | Where-Object { $_.Extension -match '^\.docx?$' }).Count
    if ($examDirs -ne 57) {
        Add-Error ("Expected 57 exam course directories, found {0}" -f $examDirs)
    }
    if ($examDocs -ne 320) {
        Add-Error ("Expected 320 Word exam files, found {0}" -f $examDocs)
    }
}

$trackedFiles = @()
try {
    $safeRootPath = $rootPath.Replace('\', '/')
    $trackedFiles = git -c ('safe.directory=' + $safeRootPath) -c core.quotepath=false ls-files 2>$null
    if ($LASTEXITCODE -ne 0) {
        throw 'git ls-files failed'
    }
} catch {
    Add-Warning 'Unable to read git tracked file list; falling back to all files.'
    $trackedFiles = Get-ChildItem -Recurse -File | ForEach-Object { Get-RelativePath $_.FullName }
}

Write-Host '== Large files =='
$oneMB = 1024 * 1024
$fiftyMB = 50 * $oneMB
$hundredMB = 100 * $oneMB
foreach ($relative in $trackedFiles) {
    $file = Join-Path $root $relative
    if (-not (Test-Path -LiteralPath $file)) { continue }
    $item = Get-Item -LiteralPath $file -ErrorAction SilentlyContinue
    if (-not $item) { continue }
    if ($item.Length -le $fiftyMB) { continue }
    if ($item.Length -gt $hundredMB) {
        Add-Error ('File exceeds 100 MB: ' + $relative + ' bytes=' + $item.Length)
    } else {
        Add-Warning ('File exceeds 50 MB: ' + $relative + ' bytes=' + $item.Length)
    }
}

Write-Host '== Temporary files =='
foreach ($relative in $trackedFiles) {
    $name = Split-Path $relative -Leaf
    if ($name -match '^~\$|\.bak$|\.tmp$|\.temp$') {
        Add-Warning ('Temporary file: ' + $relative)
    }
}

if ($warnings.Count -gt 0) {
    Write-Host ''
    Write-Host 'Warnings:'
    $warnings | ForEach-Object { Write-Host ('  - ' + $_) }
}

if ($errors.Count -gt 0) {
    Write-Host ''
    Write-Host 'Errors:'
    $errors | ForEach-Object { Write-Host ('  - ' + $_) }
    exit 1
}

Write-Host
Write-Host Audit passed
