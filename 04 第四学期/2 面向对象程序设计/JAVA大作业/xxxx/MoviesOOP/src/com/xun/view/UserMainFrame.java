package com.xun.view;

import com.xun.dao.MovieDao;

import com.xun.model.Movie;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class UserMainFrame extends JFrame {

    private MovieDao movieDao = new MovieDao();

    public UserMainFrame() {
        setTitle("User Main Frame");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();

        // 创建查找板块
        JPanel searchPanel = new JPanel(new BorderLayout());
        tabbedPane.addTab("Search", searchPanel);

        JPanel searchFormPanel = new JPanel(new GridLayout(5, 2));
        searchPanel.add(searchFormPanel, BorderLayout.NORTH);

        searchFormPanel.add(new JLabel("Actor:"));
        JTextField actorField = new JTextField();
        searchFormPanel.add(actorField);

        searchFormPanel.add(new JLabel("Director:"));
        JTextField directorField = new JTextField();
        searchFormPanel.add(directorField);

        searchFormPanel.add(new JLabel("Movie Title:"));
        JTextField titleField = new JTextField();
        searchFormPanel.add(titleField);

        searchFormPanel.add(new JLabel("Year:"));
        JTextField yearField = new JTextField();
        searchFormPanel.add(yearField);

        JButton searchButton = new JButton("Search");
        searchFormPanel.add(new JLabel(""));
        searchFormPanel.add(searchButton);

        JTextArea searchResultArea = new JTextArea();
        searchPanel.add(new JScrollPane(searchResultArea), BorderLayout.CENTER);

        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String actor = actorField.getText().trim();
                String director = directorField.getText().trim();
                String title = titleField.getText().trim();

                int year = 0;
                try {
                    if (!yearField.getText().isEmpty()) {
                        year = Integer.parseInt(yearField.getText().trim());
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(UserMainFrame.this, "Invalid year format. Use a valid year.");
                    return;
                }

                List<Movie> movies = movieDao.searchMovies(actor.isEmpty() ? null : actor,
                                                          director.isEmpty() ? null : director,
                                                          title.isEmpty() ? null : title,
                                                          year);

                searchResultArea.setText(""); // Clear previous search results

                if (movies.isEmpty()) {
                    searchResultArea.append("No movies found matching the search criteria.");
                } else {
                    for (Movie movie : movies) {
                        searchResultArea.append(movie.toString() + "\n");
                    }
                }
            }
        });


        // 创建推荐板块
        JPanel recommendationPanel = new JPanel(new BorderLayout());
        tabbedPane.addTab("Recommendations", recommendationPanel);

        JTextArea recommendationArea = new JTextArea();
        recommendationPanel.add(new JScrollPane(recommendationArea), BorderLayout.CENTER);

        // 显示每日推荐和近期热门推荐
        recommendationArea.append("Daily Recommendation:\n");
        List<Movie> dailyRecommendation = movieDao.getDailyRecommendation();
        for (Movie movie : dailyRecommendation) {
            recommendationArea.append(movie.toString() + "\n");
        }

        recommendationArea.append("\nRecent Hot Recommendations:\n");
        List<Movie> recentHotRecommendations = movieDao.getRecentHotRecommendations();
        for (Movie movie : recentHotRecommendations) {
            recommendationArea.append(movie.toString() + "\n");
        }

        getContentPane().add(tabbedPane);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new UserMainFrame().setVisible(true);
            }
        });
    }
}
