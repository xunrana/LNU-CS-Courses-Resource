package com.xun.view;

import com.xun.dao.UserDao;
import com.xun.dao.AdminDao;
import com.xun.model.Admin;
import com.xun.model.User;
import com.xun.util.StringUtil;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginFrame extends JFrame {
    private JTextField idField;
    private JPasswordField passwordField;
    private JComboBox<String> userTypeComboBox;
    private JButton loginButton;
    private JButton registerButton; // 新添加的注册按钮
    private UserDao userDao;
    private AdminDao adminDao;

    public LoginFrame() {
        userDao = new UserDao();
        adminDao = new AdminDao();

        setTitle("Login");
        setSize(350, 250); // 增加高度以适应注册按钮
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        add(panel);
        placeComponents(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                handleLogin();
            }
        });

        // 注册按钮的事件监听
        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 打开注册界面
                new RegisterFrame().setVisible(true);
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

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 165, 25);
        panel.add(passwordField);

        JLabel userTypeLabel = new JLabel("User Type:");
        userTypeLabel.setBounds(10, 80, 80, 25);
        panel.add(userTypeLabel);

        String[] userTypes = { "User", "Admin" };
        userTypeComboBox = new JComboBox<>(userTypes);
        userTypeComboBox.setBounds(100, 80, 165, 25);
        panel.add(userTypeComboBox);

        loginButton = new JButton("Login");
        loginButton.setBounds(10, 110, 80, 25);
        panel.add(loginButton);

        // 注册按钮的添加
        registerButton = new JButton("Register");
        registerButton.setBounds(100, 110, 100, 25);
        panel.add(registerButton);
    }

    private void handleLogin() {
        String id = idField.getText();
        String password = new String(passwordField.getPassword());
        String userType = (String) userTypeComboBox.getSelectedItem();

        if (StringUtil.isNullOrEmpty(id)) {
            JOptionPane.showMessageDialog(this, "ID cannot be empty");
            return;
        }

        if (StringUtil.isNullOrEmpty(password)) {
            JOptionPane.showMessageDialog(this, "Password cannot be empty");
            return;
        }

        boolean loginSuccessful = false;
        if ("User".equals(userType)) {
            User user = userDao.getUserById(Integer.parseInt(id));
            if (user != null && user.getPassword().equals(password)) {
                loginSuccessful = true;
                JOptionPane.showMessageDialog(this, "Login successful as User");
                new UserMainFrame().setVisible(true); // 跳转到用户主界面
                dispose();
            }
        } else if ("Admin".equals(userType)) {
            Admin admin = adminDao.getAdminById(Integer.parseInt(id));
            if (admin != null && admin.getPassword().equals(password)) {
                loginSuccessful = true;
                JOptionPane.showMessageDialog(this, "Login successful as Admin");
                new AdminMainFrame().setVisible(true); // 跳转到管理员主界面
                dispose();
            }
        }

        if (!loginSuccessful) {
            JOptionPane.showMessageDialog(this, "Invalid ID or Password");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginFrame().setVisible(true);
            }
        });
    }
}
