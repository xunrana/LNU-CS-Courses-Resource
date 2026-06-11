package com.xun.view;

import com.xun.dao.UserDao;
import com.xun.model.User;
import com.xun.util.StringUtil;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegisterFrame extends JFrame {
    private JTextField idField;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton registerButton;
    private UserDao userDao;

    public RegisterFrame() {
        userDao = new UserDao();

        setTitle("Register");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        add(panel);
        placeComponents(panel);

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                handleRegister();
            }
        });
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("ID:");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        idField = new JTextField(20);
        idField.setBounds(100, 20, 165, 25);
        panel.add(idField);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(10, 50, 80, 25);
        panel.add(usernameLabel);

        usernameField = new JTextField(20);
        usernameField.setBounds(100, 50, 165, 25);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 80, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 80, 165, 25);
        panel.add(passwordField);

        registerButton = new JButton("Register");
        registerButton.setBounds(100, 110, 100, 25);
        panel.add(registerButton);
    }
    private void handleRegister() {
        String idStr = idField.getText();
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        if (StringUtil.isNullOrEmpty(idStr) || StringUtil.isNullOrEmpty(username) || StringUtil.isNullOrEmpty(password)) {
            JOptionPane.showMessageDialog(this, "Please fill in all fields");
            return;
        }

        try {
            int userId = Integer.parseInt(idStr);
            
            // Register the user
            userDao.addUser(userId, username, password);
            
            JOptionPane.showMessageDialog(this, "Registration successful");
            dispose();
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Invalid ID format");
        }
    }


    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new RegisterFrame().setVisible(true);
            }
        });
    }
}
