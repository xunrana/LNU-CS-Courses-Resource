package com.xun.view;

import com.xun.dao.ActorDao;
import com.xun.dao.DirectorDao;
import com.xun.dao.MovieDao;
import com.xun.model.Actor;
import com.xun.model.Director;
import com.xun.model.Movie;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Date;
import java.text.ParseException;
import java.text.SimpleDateFormat;

public class AdminMainFrame extends JFrame {
    private JTextField directorIdField1,movieIdField,titleField, releaseDateField, durationField, ratingField, plotSummaryField, typeIdField, regionIdField;
    private JTextField actorIdField, actorNameField, actorBirthDateField;
    private JTextField directorIdField, directorNameField, directorBirthDateField;

    private MovieDao movieDao;
    private ActorDao actorDao;
    private DirectorDao directorDao;

    public AdminMainFrame() {
        movieDao = new MovieDao();
        actorDao = new ActorDao();
        directorDao = new DirectorDao();

        setTitle("Admin Main Frame");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();

        // 添加电影面板
        JPanel addMoviePanel = createAddMoviePanel();
        tabbedPane.add("添加电影", addMoviePanel);

        // 添加演员面板
        JPanel addActorPanel = createAddActorPanel();
        tabbedPane.add("添加演员", addActorPanel);

        // 添加导演面板
        JPanel addDirectorPanel = createAddDirectorPanel();
        tabbedPane.add("添加导演", addDirectorPanel);

        getContentPane().add(tabbedPane, BorderLayout.CENTER);
    }

    private JPanel createAddActorPanel() {
        JPanel panel = new JPanel(new GridLayout(4, 2));

        panel.add(new JLabel("演员ID:"));
        actorIdField = new JTextField();
        panel.add(actorIdField);

        panel.add(new JLabel("演员名字:"));
        actorNameField = new JTextField();
        panel.add(actorNameField);

        panel.add(new JLabel("出生日期 (yyyy-mm-dd):"));
        actorBirthDateField = new JTextField();
        panel.add(actorBirthDateField);

        JButton addButton = new JButton("添加演员");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addActor();
            }
        });
        panel.add(addButton);

        return panel;
    }

    private JPanel createAddDirectorPanel() {
        JPanel panel = new JPanel(new GridLayout(4, 2));

        panel.add(new JLabel("导演ID:"));
        directorIdField = new JTextField();
        panel.add(directorIdField);

        panel.add(new JLabel("导演名字:"));
        directorNameField = new JTextField();
        panel.add(directorNameField);

        panel.add(new JLabel("出生日期 (yyyy-mm-dd):"));
        directorBirthDateField = new JTextField();
        panel.add(directorBirthDateField);

        JButton addButton = new JButton("添加导演");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addDirector();
            }
        });
        panel.add(addButton);

        return panel;
    }

    private JPanel createAddMoviePanel() {
        JPanel panel = new JPanel(new GridLayout(10, 2));

        panel.add(new JLabel("电影ID:"));
        movieIdField = new JTextField();
        panel.add(movieIdField);

        panel.add(new JLabel("标题:"));
        titleField = new JTextField();
        panel.add(titleField);

        panel.add(new JLabel("上映日期 (yyyy-mm-dd):"));
        releaseDateField = new JTextField();
        panel.add(releaseDateField);

        panel.add(new JLabel("时长 (分钟):"));
        durationField = new JTextField();
        panel.add(durationField);

        panel.add(new JLabel("评分:"));
        ratingField = new JTextField();
        panel.add(ratingField);

        panel.add(new JLabel("剧情简介:"));
        plotSummaryField = new JTextField();
        panel.add(plotSummaryField);

        panel.add(new JLabel("类型ID:"));
        typeIdField = new JTextField();
        panel.add(typeIdField);

        panel.add(new JLabel("地区ID:"));
        regionIdField = new JTextField();
        panel.add(regionIdField);

        panel.add(new JLabel("导演ID:"));
        directorIdField1 = new JTextField();
        panel.add(directorIdField1);
        
        

        JButton addButton = new JButton("添加电影");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addMovie();
            }
        });
        panel.add(addButton);

        return panel;
    }

    private void addMovie() {
        try {
            String movieIdText = movieIdField.getText().trim();
            String title = titleField.getText().trim();
            String releaseDateText = releaseDateField.getText().trim();
            String durationText = durationField.getText().trim();
            String ratingText = ratingField.getText().trim();
            String plotSummary = plotSummaryField.getText().trim();
            String typeIdText = typeIdField.getText().trim();
            String regionIdText = regionIdField.getText().trim();
            String directorIdText = directorIdField1.getText().trim();

            // 调试信息
            System.out.println("电影ID: " + movieIdText);
            System.out.println("标题: " + title);
            System.out.println("上映日期: " + releaseDateText);
            System.out.println("时长: " + durationText);
            System.out.println("评分: " + ratingText);
            System.out.println("剧情简介: " + plotSummary);
            System.out.println("类型ID: " + typeIdText);
            System.out.println("地区ID: " + regionIdText);
            System.out.println("导演ID: " + directorIdText);

            int movieId = validateInteger(movieIdText, "电影ID");
            Date releaseDate = validateDate(releaseDateText, "上映日期");
            int duration = validateInteger(durationText, "时长");
            double rating = validateDouble(ratingText, "评分");
            int typeId = validateInteger(typeIdText, "类型ID");
            int regionId = validateInteger(regionIdText, "地区ID");
            int directorId = validateInteger(directorIdText, "导演ID");

            if (title.isEmpty() || plotSummary.isEmpty()) {
                JOptionPane.showMessageDialog(this, "标题和剧情简介不能为空。");
                return;
            }

            Movie movie = new Movie();
            movie.setMovieId(movieId);
            movie.setTitle(title);
            movie.setReleaseDate(releaseDate);
            movie.setDuration(duration);
            movie.setRating(rating);
            movie.setPlotSummary(plotSummary);
            movie.setTypeId(typeId);
            movie.setRegionId(regionId);
            movie.setDirectorId(directorId);

            movieDao.addMovie(movie);
            JOptionPane.showMessageDialog(this, "电影添加成功！");
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        } catch (ParseException e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        } catch (Exception e) {  // 捕获所有其他异常
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "发生错误：" + e.getMessage());
        }
    }

    private void addActor() {
        try {
            int actorId = validateInteger(actorIdField.getText(), "演员ID");
            String actorName = actorNameField.getText();
            Date birthDate = validateDate(actorBirthDateField.getText(), "出生日期");

            if (actorName.isEmpty()) {
                JOptionPane.showMessageDialog(this, "演员名字不能为空。");
                return;
            }

            // 调试信息
            System.out.println("演员ID: " + actorId);
            System.out.println("演员名字: " + actorName);
            System.out.println("出生日期: " + birthDate);

            Actor actor = new Actor();
            actor.setActorId(actorId);
            actor.setActorName(actorName);
            actor.setBirthDate(birthDate);

            actorDao.addActor(actor);
            JOptionPane.showMessageDialog(this, "演员添加成功！");
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        } catch (ParseException e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        }
    }

    private void addDirector() {
        try {
            int directorId = validateInteger(directorIdField.getText(), "导演ID");
            String directorName = directorNameField.getText();
            Date birthDate = validateDate(directorBirthDateField.getText(), "出生日期");

            if (directorName.isEmpty()) {
                JOptionPane.showMessageDialog(this, "导演名字不能为空。");
                return;
            }

            // 调试信息
            System.out.println("导演ID: " + directorId);
            System.out.println("导演名字: " + directorName);
            System.out.println("出生日期: " + birthDate);

            Director director = new Director();
            director.setDirectorId(directorId);
            director.setDirectorName(directorName);
            director.setBirthDate(birthDate);

            directorDao.addDirector(director);
            JOptionPane.showMessageDialog(this, "导演添加成功！");
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        } catch (ParseException e) {
            JOptionPane.showMessageDialog(this, e.getMessage());
        }
    }

    private int validateInteger(String text, String fieldName) throws NumberFormatException {
        try {
            return Integer.parseInt(text);
        } catch (NumberFormatException e) {
            throw new NumberFormatException(fieldName + " 必须是有效的整数。");
        }
    }

    private double validateDouble(String text, String fieldName) throws NumberFormatException {
        try {
            return Double.parseDouble(text);
        } catch (NumberFormatException e) {
            throw new NumberFormatException(fieldName + " 必须是有效的数字。");
        }
    }

    private Date validateDate(String text, String fieldName) throws ParseException {
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
            return new Date(sdf.parse(text).getTime());
        } catch (ParseException e) {
            throw new ParseException(fieldName + " 必须是有效的日期，格式为 yyyy-mm-dd。", e.getErrorOffset());
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new AdminMainFrame().setVisible(true);
            }
        });
    }
}
