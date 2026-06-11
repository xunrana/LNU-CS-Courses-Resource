int count(int A[], int left, int right) {
    // 在数组A中，求出[left, right]区间内的逆序对个数
    if (left == right) return 0;
    int mid = (left + right) / 2;
    int leftCount = count(A, left, mid);
    int rightCount = count(A, mid + 1, right);
    int crossCount = 0;
    int* temp = new int[right - left + 1];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        }
        else {
            temp[k++] = A[j++];
            crossCount += mid - i + 1;
        }
    }
    while (i <= mid) {
        temp[k++] = A[i++];
    }
    while (j <= right) {
        temp[k++] = A[j++];
    }
    for (int i = 0; i < k; i++) {
        A[left + i] = temp[i];
    }
    return leftCount + rightCount + crossCount;
}

FUNCTION count(A, left, right)
    IF left = right THEN
        RETURN 0
    END IF
    mid <- (left + right) / 2
    leftCount <- count(A, left, mid)
    rightCount <- count(A, mid + 1, right)
    crossCount <- 0
    temp <- new int[right - left + 1]
    i <- left, j <- mid + 1, k <- 0
    WHILE i <= mid AND j <= right DO
        IF A[i] <= A[j] THEN
            temp[k++] <- A[i++]
        ELSE
            temp[k++] <- A[j++]
            crossCount <- crossCount + (mid - i + 1)
        END IF
    END WHILE
    WHILE i <= mid DO
        temp[k++] <- A[i++]
    END WHILE
    WHILE j <= right DO
        temp[k++] <- A[j++]
    END WHILE
    FOR i <- 0 TO k-1 DO
        A[left + i] <- temp[i]
    END FOR
    RETURN leftCount + rightCount + crossCount
END FUNCTION

void solve(int N, int C, int p[], int v[]) {
    // N件物品，背包容量为C，第i件物品的重量为p[i]，价值为v[i]
    int dp[N + 1][C + 1];   // dp[i][j]表示前i种菜，报销额度为j时的最大评分
    int s[N + 1][C + 1];    // s[i][j]表示前i种菜，报销额度为j时，是否点了第i种菜
    // 边界处理：没有菜时，或者报销额度为0时，最大评分都为0
    for (int i = 0; i <= N; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= C; j++)
        dp[0][j] = 0;
    // 状态转移方程：dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - p[i]] + v[i])
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= C; j++) {
            if (j < p[i]) {
                // 报销额度不够，只能不点这道菜
                dp[i][j] = dp[i - 1][j];
                s[i][j] = 0;
            } else {
                if (dp[i - 1][j] > dp[i - 1][j - p[i]] + v[i]) {
                    // 不点这道菜
                    dp[i][j] = dp[i - 1][j];
                    s[i][j] = 0;
                } else {
                    // 点这道菜
                    dp[i][j] = dp[i - 1][j - p[i]] + v[i];
                    s[i][j] = 1;
                }
            }
        }
    }
}

FUNCTION solve(N, C, p[], v[])
    dp[N + 1][C + 1]
    s[N + 1][C + 1]
    FOR i <- 0 TO N DO
        dp[i][0] <- 0
    END FOR
    FOR j <- 0 TO C DO
        dp[0][j] <- 0
    END FOR
    FOR i <- 1 TO N DO
        FOR j <- 1 TO C DO
            IF j < p[i] THEN
                dp[i][j] <- dp[i - 1][j]
                s[i][j] <- 0
            ELSE
                IF dp[i - 1][j] > dp[i - 1][j - p[i]] + v[i] THEN
                    dp[i][j] <- dp[i - 1][j]
                    s[i][j] <- 0
                ELSE
                    dp[i][j] <- dp[i - 1][j - p[i]] + v[i]
                    s[i][j] <- 1
                END IF
            END IF
        END FOR
    END FOR
END FUNCTION

void solve(double income[4][8]) {
    double dp[4][8];   // dp[i][j]表示前i个项目，投资j万元时的最大收益
    double s[4][8] = { 0 };  // sum[i][j]表示前i个项目，投资j万元时，对第i个项目的投资，用于追溯解路径 

    // 边界处理：没有项目时，或者投资额度为0时，最大收益都为0
    for (int i = 0; i <= 3; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= 7; j++)
        dp[0][j] = 0;
    // 状态转移方程（不投、投1...投j万元）：dp[i][j] = max(dp[i - 1][j - k] + income[i][k]) (0 <= k <= j)
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 7; j++) {
            double max = 0;
            for (int k = 0; k <= j; k++) {
                if (dp[i - 1][j - k] + income[i][k] > max) {
                    max = dp[i - 1][j - k] + income[i][k];
                    s[i][j] = k;
                }
            }
            dp[i][j] = max;
        }
    }
}

FUNCTION solve(income[4][8])
    dp[4][8]
    s[4][8] <- 0
    FOR i <- 0 TO 3 DO
        dp[i][0] <- 0
    END FOR
    FOR j <- 0 TO 7 DO
        dp[0][j] <- 0
    END FOR
    FOR i <- 1 TO 3 DO
        FOR j <- 1 TO 7 DO
            max <- 0
            FOR k <- 0 TO j DO
                IF dp[i - 1][j - k] + income[i][k] > max THEN
                    max <- dp[i - 1][j - k] + income[i][k]
                    s[i][j] <- k
                END IF
            END FOR
            dp[i][j] <- max
        END FOR
    END FOR
END FUNCTION

void solve(struct Meeting meetings[]) {
    // 每个会议有两种选择：开或者不开
    int dp[12][25];     // 前i个会议，会议室使用时间为0~j时的最大持续时间
    int s[12][25] = { 0 };  // sum[i][j]表示前i个会议，会议室使用时间为j时，对第i个会议的选择，0不开，1开
    // 边界处理：没有会议时，或者会议室使用时间为0时，最大持续时间都为0
    for (int i = 0; i < 12; i++)
        dp[i][0] = 0;
    for (int j = 0; j < 25; j++)
        dp[0][j] = 0;
    // 状态转移方程：dp[i][j] = max(dp[i - 1][j], dp[i - 1][meetings[i].start] + meetings[i].duration)
    for (int i = 1; i < 12; i++) {
        for (int j = 1; j < 25; j++) {
            if (j < meetings[i].end)
                dp[i][j] = dp[i - 1][j];
            else {
                if (dp[i - 1][j] > dp[i - 1][meetings[i].start] + meetings[i].duration) {
                    dp[i][j] = dp[i - 1][j];
                    s[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][meetings[i].start] + meetings[i].duration;
                    s[i][j] = 1;
                }
            }
        }
    }
}

FUNCTION solve(meetings[])
    dp[12][25]
    s[12][25] <- 0
    FOR i <- 0 TO 11 DO
        dp[i][0] <- 0
    END FOR
    FOR j <- 0 TO 24 DO
        dp[0][j] <- 0
    END FOR
    FOR i <- 1 TO 11 DO
        FOR j <- 1 TO 24 DO
            IF j < meetings[i].end THEN
                dp[i][j] <- dp[i - 1][j]
            ELSE
                IF dp[i - 1][j] > dp[i - 1][meetings[i].start] + meetings[i].duration THEN
                    dp[i][j] <- dp[i - 1][j]
                    s[i][j] <- 0
                ELSE
                    dp[i][j] <- dp[i - 1][meetings[i].start] + meetings[i].duration
                    s[i][j] <- 1
                END IF
            END IF
        END FOR
    END FOR
    END FUNCTION

void sove(struct Meeting meetings[], int n) {
    bool exist[12] = { false }; // 标记会议是否已经安排
    // 此处使用贪心算法，每次选择结束时间最早的会议
    sort(meetings + 1, meetings + 12, [](Meeting a, Meeting b) {
        return a.end < b.end;
        });
    int count = 0;  // 会场个数
    int end = 0;    // 当前会场的结束时间
    for (int i = 1; i <= 11; i++) {
        if (!exist[i]) {
            count++;
            exist[i] = true;
            end = meetings[i].end;
            cout << endl << "会场" << count << "：会议" << i << " ";
            for (int j = i + 1; j <= 11; j++) {
                if (!exist[j] && meetings[j].start >= end) {
                    exist[j] = true;
                    end = meetings[j].end;  // 更新会场的结束时间
                    cout << "会议" << j << " ";
                }
            }
        }
    }
    cout << endl << "最少的会场个数为：" << count << endl;
}

FUNCTION solve(meetings[], n)
    exist[12] <- false
    sort(meetings + 1, meetings + 12, [](Meeting a, Meeting b) {
        return a.end < b.end;
        })
    count <- 0
    end <- 0
    FOR i <- 1 TO 11 DO
        IF !exist[i] THEN
            count <- count + 1
            exist[i] <- true
            end <- meetings[i].end
            PRINT "会场" + count + "：会议" + i + " "
            FOR j <- i + 1 TO 11 DO
                IF !exist[j] AND meetings[j].start >= end THEN
                    exist[j] <- true
                    end <- meetings[j].end
                    PRINT "会议" + j + " "
                END IF
            END FOR
        END IF
    END FOR
    PRINT "最少的会场个数为：" + count
            END FUNCTION

    // n个人，第i个人的体重为w[i]，船的最大载重量为C
    sort(w + 1, w + n + 1); // 从小到大排序
    int i = 1, j = n;       // i指向最轻的人，j指向最重的人
    int count = 0;          // 船的数量
    while (i <= j) {
        if (w[i] + w[j] <= C) {
            // 最轻的人和最重的人可以坐在一艘船上
            cout << "第" << ++count << "艘船：" << w[i] << " " << w[j] << endl;
            i++;
            j--;
        }
        else {
            // 最重的人只能单独坐一艘船
            cout << "第" << ++count << "艘船：" << w[j] << endl;
            j--;
        }
    }
    cout << "最少的船的数量为：" << count << endl;
}

FUNCTION solve(w[], n, C)
    sort(w + 1, w + n + 1)
    i <- 1
    j <- n
    count <- 0
    WHILE i <= j DO
        IF w[i] + w[j] <= C THEN
            PRINT "第" + ++count + "艘船：" + w[i] + " " + w[j]
            i <- i + 1
            j <- j - 1
        ELSE
            PRINT "第" + ++count + "艘船：" + w[j]
            j <- j - 1
        END IF
    END WHILE
    PRINT "最少的船的数量为：" + count
END FUNCTION

void solve(struct Meeting meetings[]) {
    // 每个会议有两种选择：开或者不开
    int dp[12][25];     // 前i个会议，会议室使用时间为0~j时的最大持续时间
    int s[12][25] = { 0 };  // sum[i][j]表示前i个会议，会议室使用时间为j时，对第i个会议的选择，0不开，1开
    // 边界处理：没有会议时，或者会议室使用时间为0时，最大持续时间都为0
    for (int i = 0; i < 12; i++)
        dp[i][0] = 0;
    for (int j = 0; j < 25; j++)
        dp[0][j] = 0;
    // 状态转移方程：dp[i][j] = max(dp[i - 1][j], dp[i - 1][meetings[i].start] + meetings[i].duration)
    for (int i = 1; i < 12; i++) {
        for (int j = 1; j < 25; j++) {
            if (j < meetings[i].end)
                dp[i][j] = dp[i - 1][j];
            else {
                if (dp[i - 1][j] > dp[i - 1][meetings[i].start] + meetings[i].duration) {
                    dp[i][j] = dp[i - 1][j];
                    s[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][meetings[i].start] + meetings[i].duration;
                    s[i][j] = 1;
                }
            }
        }
    }

    // 追溯解路径
    int i = 11, j = 24;
    while (i > 0) {
        if (s[i][j] == 1) {
            cout << "第" << i << "个会议开" << endl;
            j = meetings[i].start;
            cout << "会议室使用时间：" << j << "~" << meetings[i].end << endl;
        }
        i--;
    }
}

FUNCTION solve(meetings[])
    dp[12][25]
    s[12][25] <- 0
    FOR i <- 0 TO 11 DO
        dp[i][0] <- 0
    END FOR
    FOR j <- 0 TO 24 DO
        dp[0][j] <- 0
    END FOR
    FOR i <- 1 TO 11 DO
        FOR j <- 1 TO 24 DO
            IF j < meetings[i].end THEN
                dp[i][j] <- dp[i - 1][j]
            ELSE
                IF dp[i - 1][j] > dp[i - 1][meetings[i].start] + meetings[i].duration THEN
                    dp[i][j] <- dp[i - 1][j]
                    s[i][j] <- 0
                ELSE
                    dp[i][j] <- dp[i - 1][meetings[i].start] + meetings[i].duration
                    s[i][j] <- 1
                END IF
            END IF
        END FOR
    END FOR
    i <- 11
    j <- 24
    WHILE i > 0 DO
        IF s[i][j] == 1 THEN
            PRINT "第" + i + "个会议开"
            j <- meetings[i].start
            PRINT "会议室使用时间：" + j + "~" + meetings[i].end
        END IF
        i <- i - 1
    END WHILE
    END FUNCTION

void solve(int a[], int n) {
    sort(a, a + n);
    int max = a[0], maxCount = 0;   // max：整个数组的众数，maxCount：整个数组的众数出现的次数
    int temp = a[0], tempCount = 0; // temp：当前元素，tempCount：当前元素出现的次数
    for (int i = 0; i < n; i++) {
        if (a[i] == temp) {
            tempCount++;
        }
        else {
            temp = a[i];
            tempCount = 1;
        }
        if (tempCount > maxCount) {
            max = temp;
            maxCount = tempCount;
        }
    }
    cout << max << "，出现次数：" << maxCount << endl;
}

FUNCTION solve(a[], n)
    sort(a, a + n)
    max <- a[0]
    maxCount <- 0
    temp <- a[0]
    tempCount <- 0
    FOR i <- 0 TO n - 1 DO
        IF a[i] == temp THEN
            tempCount <- tempCount + 1
        ELSE
            temp <- a[i]
            tempCount <- 1
        END IF
        IF tempCount > maxCount THEN
            max <- temp
            maxCount <- tempCount
        END IF
    END FOR
    PRINT max + "，出现次数：" + maxCount
END FUNCTION
    
void recall_solve() {
    int min = 1000000;
    int path[M] = {0};
    // 路径 i -> j -> k -> l -> i
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j) continue;   // 不满足约束条件
            for (int k = 0; k < M; k++) {
                if (i == k || j == k) continue; // 不满足约束条件
                for (int l = 0; l < M; l++) {
                    if (i == l || j == l || k == l) continue; // 不满足约束条件
                    int sum = a[i][j] + a[j][k] + a[k][l] + a[l][i];
                    if (sum < min) {
                        min = sum;
                        path[0] = i;
                        path[1] = j;
                        path[2] = k;
                        path[3] = l;
                    }
                }
            }
        }
    }
    cout << "回溯法：\n\t最短长度：" << min << endl;
    cout << "\t最短路径：";
    for (int i = 0; i < M; i++) cout << path[i] << " ";
    cout << endl;
}

FUNCTION recall_solve()
    min <- 1000000
    path[M] <- 0
    FOR i <- 0 TO M - 1 DO
        FOR j <- 0 TO M - 1 DO
            IF i == j THEN
                CONTINUE
            END IF
            FOR k <- 0 TO M - 1 DO
                IF i == k OR j == k THEN
                    CONTINUE
                END IF
                FOR l <- 0 TO M - 1 DO
                    IF i == l OR j == l OR k == l THEN
                        CONTINUE
                    END IF
                    sum <- a[i][j] + a[j][k] + a[k][l] + a[l][i]
                    IF sum < min THEN
                        min <- sum
                        path[0] <- i
                        path[1] <- j
                        path[2] <- k
                        path[3] <- l
                    END IF
                END FOR
            END FOR
        END FOR
    END FOR
    PRINT "回溯法："
    PRINT "\t最短长度：" + min
    PRINT "\t最短路径："
    FOR i <- 0 TO M - 1 DO
        PRINT path[i] + " "
    END FOR
END FUNCTION

void dfs(int i) {
    // 决策第i个数是否选中
    if (i >= N) return;
    if (sum == k) {
        count++;
        int j;
        for (j = 0; j < N; j++) {
            if (x[j] == 1) {
                cout << a[j];
                break;
            }
        }
        for (j = j + 1; j < N; j++) {
            if (x[j] == 1) cout << " + " << a[j];
        }
        cout << " = " << k << endl;
        return;
    }
    // 选中第i个数
    x[i] = 1;
    sum += a[i];
    dfs(i + 1);
    // 不选中第i个数
    x[i] = 0;
    sum -= a[i];
    dfs(i + 1);
}

FUNCTION dfs(i)
    IF i >= N THEN
        RETURN
    END IF
    IF sum == k THEN
        count <- count + 1
        FOR j <- 0 TO N - 1 DO
            IF x[j] == 1 THEN
                PRINT a[j]
                BREAK
            END IF
        END FOR
        FOR j <- j + 1 TO N - 1 DO
            IF x[j] == 1 THEN
                PRINT " + " + a[j]
            END IF
        END FOR
        PRINT " = " + k
        RETURN
    END IF
    x[i] <- 1
    sum <- sum + a[i]
    dfs(i + 1)
    x[i] <- 0
    sum <- sum - a[i]
    dfs(i + 1)
END FUNCTION

void dfs(int u) {
    // u 表示当前行-1
    if (u == N) {
        // 已经决策完毕
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << g[i][j] << " ";
            cout << endl;
        }
        cout << "-----------------\n";
        return;
    }
    // 枚举第u行的所有列，判断是否可以放置皇后
    for (int i = 0; i < N; i++) {
        // 不满足约束条件的，不再继续
        if (!col[i] && !dg[u - i + N] && !udg[u + i]) {
            // 即同一主对角线上的点，行-列的值相等，同一副对角线上的点，行+列的值相等
            g[u][i] = 'Q';
            col[i] = dg[u - i + N] = udg[u + i] = true;
            dfs(u + 1);
            // 回溯
            col[i] = dg[u - i + N] = udg[u + i] = false;
            g[u][i] = '.';
        }
    }
}

void queen_solve() {
    // 使用回溯法求解N皇后问题
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            g[i][j] = '.';
    dfs(0);
}

FUNCTION dfs(u)
    IF u == N THEN
        FOR i <- 0 TO N - 1 DO
            FOR j <- 0 TO N - 1 DO
                PRINT g[i][j] + " "
            END FOR
            PRINT "\n"
        END FOR
        PRINT "-----------------\n"
        RETURN
    END IF
    FOR i <- 0 TO N - 1 DO
        IF NOT col[i] AND NOT dg[u - i + N] AND NOT udg[u + i] THEN
            g[u][i] <- 'Q'
            col[i] <- TRUE
            dg[u - i + N] <- TRUE
            udg[u + i] <- TRUE
            dfs(u + 1)
            col[i] <- FALSE
            dg[u - i + N] <- FALSE
            udg[u + i] <- FALSE
            g[u][i] <- '.'
        END IF
    END FOR
END FUNCTION

void bfs() {
    priority_queue<State> q; // 定义优先队列

    // 将起点加入优先队列
    q.push(State(s, 0, 1));

    while (!q.empty()) {
        State curState = q.top(); // 取出队首状态
        q.pop(); // 弹出队首状态

        // 如果当前路径长度已经大于之前的最短路径，剪枝
        if (curState.sum >= minSum) {
            continue;
        }

        path[curState.cnt-1] = curState.cur; // 将当前节点加入路径

        // 如果已经到达终点，更新最短路径长度及经过的路径条数
        if (curState.cur == t) {
            if (curState.sum < minSum) {
                minSum = curState.sum;
                cnt = curState.cnt;
            } else if (curState.sum == minSum) {
                cnt += curState.cnt;
            }
            continue; // 注意要跳过后面的扩展操作
        }

        // 扩展当前状态的子状态
        for (int i = 0; i < N; i++) {
            if (graph[curState.cur][i] != 0) { // 如果当前节点能到达节点 i
                State nextState(i, curState.sum + graph[curState.cur][i], curState.cnt+1); // 构造子状态
                q.push(nextState); // 加入优先队列，自动按照路径长度排序
            }
        }
    }
}

FUNCTION bfs()
    DECLARE q AS priority_queue<State>
    q.push(State(s, 0, 1))
    WHILE NOT q.empty() DO
        DECLARE curState AS q.top()
        q.pop()
        IF curState.sum >= minSum THEN
            CONTINUE
        END IF
        path[curState.cnt-1] <- curState.cur
        IF curState.cur == t THEN
            IF curState.sum < minSum THEN
                minSum <- curState.sum
                cnt <- curState.cnt
            ELSE IF curState.sum == minSum THEN
                cnt <- cnt + curState.cnt
            END IF
            CONTINUE
        END IF
        FOR i <- 0 TO N - 1 DO
            IF graph[curState.cur][i] != 0 THEN
                DECLARE nextState AS State(i, curState.sum + graph[curState.cur][i], curState.cnt+1)
                q.push(nextState)
            END IF
        END FOR
    END WHILE
END FUNCTION

void bfs() {
    priority_queue<State> q; // 定义优先队列

    // 将起点加入优先队列
    q.push(State(0, 0, 0));

    while (!q.empty()) {
        State curState = q.top(); // 取出队首状态
        q.pop(); // 弹出队首状态

        // 如果已经装满且当前方案比之前的更优，则更新答案
        if (curState.sum == W && (ans == 0 || curState.cnt < ans)) {
            ans = curState.cnt;
        }

        // 如果当前方案已经不可能是最优方案，则剪枝
        if (ans != 0 && curState.cnt >= ans) {
            continue;
        }

        // 扩展当前状态的子状态
        if (curState.cur < n) {
            // 不选当前集装箱
            q.push(State(curState.cur + 1, curState.sum, curState.cnt));
            // 选当前集装箱
            if (curState.sum + w[curState.cur] <= W) { // 如果能装下当前集装箱
                q.push(State(curState.cur + 1, curState.sum + w[curState.cur], curState.cnt + 1));
            }
        }
    }
}

FUNCTION bfs()
    DECLARE q AS priority_queue<State>
    q.push(State(0, 0, 0))
    WHILE NOT q.empty() DO
        DECLARE curState AS q.top()
        q.pop()
        IF curState.sum == W AND (ans == 0 OR curState.cnt < ans) THEN
            ans <- curState.cnt
        END IF
        IF ans != 0 AND curState.cnt >= ans THEN
            CONTINUE
        END IF
        IF curState.cur < n THEN
            q.push(State(curState.cur + 1, curState.sum, curState.cnt))
            IF curState.sum + w[curState.cur] <= W THEN
                q.push(State(curState.cur + 1, curState.sum + w[curState.cur], curState.cnt + 1))
            END IF
        END IF
    END WHILE
END FUNCTION