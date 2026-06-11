import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import static java.awt.Font.PLAIN;

/**
 * @author Yitong Hong
 */
public class GUI {

    public static ValidInput vi = new ValidInput();

    public static void main(String[] args) {


        Frame frame = new Frame("Converter");
        frame.setBounds(200, 100, 1600, 800);

        frame.setLayout(null);
        frame.setFont(new Font("Heiti SC", PLAIN, 24));
        frame.setBackground(Color.DARK_GRAY);
        Label lexp = new Label("输入表达式");
        Label lnum = new Label("变量个数");
        Label lrev = new Label("反演");
        Label ldual = new Label("对偶");
        Label lsao = new Label("标准与或式");
        Label lsoa = new Label("标准或与式");
        Label lsm = new Label("最小项之和");
        Label lmt = new Label("最大项之积");
        Label lsp = new Label("最简与或");
        Label lAnAn=new Label("与非与非");
        Label loan=new Label("或与非");
        Label loa=new Label("或与");
        Label laon=new Label("与或非");



        lexp.setBounds(50, 50, 130, 60);
        lnum.setBounds(50, 100, 130, 60);
        lrev.setBounds(50, 150, 130, 60);
        ldual.setBounds(50, 200, 130, 60);
        lsao.setBounds(50, 250, 130, 60);
        lsoa.setBounds(50, 300, 130, 60);
        lsm.setBounds(50, 350, 130, 60);
        lmt.setBounds(50, 400, 130, 60);
        lsp.setBounds(50, 450, 130, 60);
        lAnAn.setBounds(50, 500, 130, 60);
        loan.setBounds(50, 550, 130, 60);
        loa.setBounds(50, 600, 130, 60);
        laon.setBounds(50, 650, 130, 60);



        lexp.setForeground(Color.white);
        lnum.setForeground(Color.white);
        lrev.setForeground(Color.white);
        ldual.setForeground(Color.white);
        lsao.setForeground(Color.white);
        lsoa.setForeground(Color.white);
        lsm.setForeground(Color.white);
        lmt.setForeground(Color.white);
        lsp.setForeground(Color.white);
        lAnAn.setForeground(Color.white);
        loan.setForeground(Color.white);
        loa.setForeground(Color.white);
        laon.setForeground(Color.white);

//        lrev.setBackground(Color.GRAY);


        TextField exp = new TextField();
        TextField num = new TextField();
        TextField rev = new TextField();
        TextField dual = new TextField();
        TextField sao = new TextField();
        TextField soa = new TextField();
        TextField sm = new TextField();
        TextField mt = new TextField();
        TextField sp = new TextField();
        TextField AnAn = new TextField();
        TextField oan = new TextField();
        TextField oa = new TextField();
        TextField aon = new TextField();
        exp.setBounds(200, 60, 1150, 38);
        num.setBounds(200, 110, 1150, 38);
        rev.setBounds(200, 160, 1150, 38);
        dual.setBounds(200, 210, 1150, 38);
        sao.setBounds(200, 260, 1150, 38);
        soa.setBounds(200, 310, 1150, 38);
        sm.setBounds(200, 360, 1150, 38);
        mt.setBounds(200, 410, 1150, 38);
        sp.setBounds(200, 460, 1150, 38);
        AnAn.setBounds(200, 510, 1150, 38);
        oan.setBounds(200, 560, 1150, 38);
        oa.setBounds(200, 610, 1150, 38);
        aon.setBounds(200, 660, 1150, 38);
        frame.add(exp);
        frame.add(num);
        frame.add(rev);
        frame.add(dual);
        frame.add(sao);
        frame.add(soa);
        frame.add(sm);
        frame.add(mt);
        frame.add(sp);
        frame.add(AnAn);
        frame.add(oan);
        frame.add(oa);
        frame.add(aon);

        Button okBt = new Button("ok");
        Button truthtableBT = new Button("真值表");


        okBt.addActionListener(new MyCpListener(exp, rev, num, dual, sao, soa, sm, mt, sp,AnAn,oan,oa,aon));
        okBt.setBounds(1400, 60, 80, 40);
        truthtableBT.addActionListener(new TruthTableListener());
        truthtableBT.setBounds(1400, 120, 80, 40);


        frame.add(okBt);
        frame.add(truthtableBT);


        frame.add(lexp);
        frame.add(lnum);
        frame.add(lrev);
        frame.add(ldual);
        frame.add(lsao);
        frame.add(lsoa);
        frame.add(lsm);
        frame.add(lmt);
        frame.add(lsp);
        frame.add(lAnAn);
        frame.add(loan);
        frame.add(loa);
        frame.add(laon);
        frame.setVisible(true);
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
//                frame.dispose();// System.exit(0);

                System.exit(0);
            }
        });
        frame.addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                System.out.println(e.getKeyChar());
            }
        });

        frame.setVisible(true);
    }

    static class MyCpListener implements ActionListener {
        public TextField exp, rev, num, dual, sao, soa, sm, mt, sp,AnAn,oan,oa,aon;


        public MyCpListener(TextField exp, TextField rev, TextField num, TextField dual, TextField sao,
                            TextField soa, TextField sm, TextField mt, TextField sp,TextField AnAn,
                            TextField oan,TextField oa,TextField aon) {
            this.exp = exp;
            this.rev = rev;
            this.num = num;
            this.dual = dual;
            this.sao = sao;
            this.soa = soa;
            this.sm = sm;
            this.mt = mt;
            this.sp = sp;
            this.AnAn=AnAn;
            this.oan=oan;
            this.oa=oa;
            this.aon=aon;
        }


        @Override
        public void actionPerformed(ActionEvent e) {
            if (Tools.check(exp.getText())) {
                if (num.getText().isEmpty()) {

                    vi.expression = exp.getText();
                    vi.obtainNumOfVariables();
                } else {

                    vi.expression = exp.getText();
                    vi.numOfVariables = Integer.parseInt(num.getText());
                }
                vi.obtainInversion();//反演与数字无关
                vi.obtainTruthTable();
                vi.obtainDual();
                vi.standardAndOr=Tools.AnyToStandardAndOr(vi.expression,vi.numOfVariables);
                vi.standardOrAnd=Tools.AnyToStandardOrAnd(vi.expression,vi.numOfVariables);
                rev.setText(vi.Inversion);
                dual.setText(vi.dual);
                sao.setText(vi.standardAndOr);
                soa.setText(vi.standardOrAnd);
                sm.setText(Tools.SumFromAndor(vi.standardAndOr,vi.numOfVariables));
                mt.setText(Tools.MultiFromAndor(vi.standardAndOr,vi.numOfVariables));
                sp.setText(Tools.getSimplestAndor(vi.expression));
                AnAn.setText(Tools.obtainAnAnFromexp(vi.expression));
                oan.setText(Tools.obtainOrAndNotFromexp (vi.expression));
                oa.setText(Tools.obtainOrAndFromexp(vi.expression));
                aon.setText(Tools.obtainOrAndNotFromexp(vi.expression));
            } else {
                new JDialog(new MyDialogDemo());
            }
        }

        static class MyDialogDemo extends JDialog {
            public MyDialogDemo() {
                this.setVisible(true);
                this.setBounds(750, 100, 400, 150);
                Container container = this.getContentPane();
                Label label = new Label("输入错误");
                Font font = new Font("Heiti SC", PLAIN, 24);
                label.setFont(font);
                container.add(label);
            }
        }
    }

    static class TruthTableListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            new Dialog(new TruthTableDialog());
        }

        static class TruthTableDialog extends JDialog {
            public TruthTableDialog() {
                this.setVisible(true);
                this.setBounds(400, 500, 800, 800);
                Container container = this.getContentPane();
                JTextArea textArea = new JTextArea(vi.showTruthTable());
                Font font = new Font("Heiti SC", PLAIN, 30);
                textArea.setFont(font);
                container.add(textArea);
            }
        }
    }



}







