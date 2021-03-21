import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import net.spy.memcached.MemcachedClient;
import java.net.*;
import java.util.concurrent.Future;
import javax.swing.JOptionPane;


public class NoSQLPJ {
    private JTextField textField1;
    private JTextField textField2;
    private JButton 插入数据Button;
    private JButton 更新数据Button;
    private JButton 查找数据Button;
    private JButton 向后追加数据Button;
    private JButton 删除数据Button;
    private JPanel Panel1;
    private JTable table1;
    private JButton 向前追加数据Button;
    private JButton 数据自增Button;
    private JButton 数据自减Button;
    private JButton 从表格中删除Button;

    //表格参数
    static DefaultTableModel model;
    static Vector title = new Vector(); //标题
    static Vector content = new Vector(); //内容
    static Vector row = new Vector(); //各个内容组成

    public NoSQLPJ() {

        插入数据Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                table1.setEnabled(false);
                String Key=textField1.getText();
                String Value=textField2.getText();
                Insert(Key,Value);
                table1.setModel(model);
            }
        });

        更新数据Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                table1.setEnabled(false);
                String Key=textField1.getText();
                String Value=textField2.getText();
                Update(Key,Value);
                table1.setModel(model);
            }
        });

        查找数据Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                table1.setEnabled(false);
                String Key=textField1.getText();
                Get(Key);
                table1.setModel(model);
            }
        });

        向前追加数据Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                table1.setEnabled(false);
                String Key=textField1.getText();
                String Value=textField2.getText();
                Prepend(Key,Value);
                table1.setModel(model);
            }
        });

        向后追加数据Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                table1.setEnabled(false);
                String Key=textField1.getText();
                String Value=textField2.getText();
                Append(Key,Value);
                table1.setModel(model);
            }
        });

        删除数据Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                table1.setEnabled(false);
                String Key=textField1.getText();
                Delete(Key);
                table1.setModel(model);
            }
        });

        数据自增Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String Key=textField1.getText();
                String Value=textField2.getText();
                Inc(Key, Value);
                table1.setModel(model);
            }
        });

        数据自减Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String Key=textField1.getText();
                String Value=textField2.getText();
                Dec(Key, Value);
                table1.setModel(model);
            }
        });
        
        从表格中删除Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String Key=textField1.getText();
                Drop(Key);
                table1.setModel(model);
            }
        });
    }

    //插入数据
    private static void Insert(String Key, String Value){
        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));
            // 存储数据
            Future fo = mcc.add(Key, 1800, Value);

            if(fo.get().toString().equals("true")){
                row.add(Key); row.add(Value); content.add(row.clone()); row.clear();
                model = new DefaultTableModel(content,title);
                mcc.shutdown();
                return ;
            }
            else{
                JOptionPane.showMessageDialog(null,"数据库中已有相同Key", "插入错误",JOptionPane.ERROR_MESSAGE);
                // 关闭连接
                mcc.shutdown();
                return ;
            }
        }catch(Exception ex){
            System.out.println( ex.getMessage() );
        }
    }

    //更新数据
    private static void Update(String Key, String Value){
        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));
            // 更新数据
            Future fo = mcc.replace(Key,1800,Value);

            //成功更新
            boolean Ifin=false;
            if(fo.get().toString().equals("true")){
                for(int i=0;i<content.size();i++){
                    String s=content.get(i).toString();
                    //在表格内
                    if (Key.equals(s.substring(1,s.indexOf(",")))){
                        row.add(Key); row.add(Value);
                        content.set(i,row.clone()); row.clear();
                        Ifin=true; break;
                    }
                }
                //不在表格内
                if(Ifin==false){
                    row.add(Key); row.add(Value);
                    content.add(row.clone()); row.clear();
                }
                mcc.shutdown();
                model = new DefaultTableModel(content,title);
                return ;
            }
            //更新失败
            else{
                JOptionPane.showMessageDialog(null,"数据库中无目标Key", "更新错误",JOptionPane.ERROR_MESSAGE);
                // 关闭连接
                mcc.shutdown();
                return ;
            }
        }catch(Exception ex){
            System.out.println( ex.getMessage() );
        }
    }

    //查找数据
    private static void Get(String Key){
        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));

            //查找数据
            if(!(mcc.get(Key).toString().equals("null"))){
                row.add(Key); row.add(mcc.get(Key).toString());
                //不在表格内
                if(!content.contains(row.clone())){
                    content.add(row.clone()); row.clear();
                    model = new DefaultTableModel(content,title);
                }
                //在表格内
                else{
                    row.clear();
                    int i=0;
                    for( ; i<content.size();i++){
                        String s=content.get(i).toString();
                        if (Key.equals(s.substring(1,s.indexOf(","))))
                            break;
                    }

                    JOptionPane.showMessageDialog(null,"目标Key已在表格中的第"+(i+1)+"行", "目标已显示",JOptionPane.WARNING_MESSAGE);
                }
                mcc.shutdown(); return ;
            }
        }catch(Exception ex){
            JOptionPane.showMessageDialog(null,"数据库中无目标Key", "查找错误",JOptionPane.ERROR_MESSAGE);
        }
    }

    //向前追加数据
    private static void Prepend(String Key, String Value){
        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));
            //向前追加数据
            Future fo = mcc.prepend(Key, Value);

            boolean Ifin=false;
            //成功追加
            if(fo.get().toString().equals("true")){
                for(int i=0;i<content.size();i++){
                    String s=content.get(i).toString();
                    //在表格内
                    if (Key.equals(s.substring(1,s.indexOf(",")))){
                        row.add(Key); row.add( Value.concat( (s.substring(s.indexOf(",")+2,s.length()-1) ) ));
                        content.set(i,row.clone()); row.clear();
                        Ifin=true; break;
                    }
                }
                //不在表格内
                if(Ifin==false){
                    row.add(Key); row.add(mcc.get(Key).toString());
                    content.add(row.clone()); row.clear();
                }
                mcc.shutdown();
                model = new DefaultTableModel(content,title);
                return ;
            }
            //追加失败
            else{
                JOptionPane.showMessageDialog(null,"数据库中无目标Key", "追加错误",JOptionPane.ERROR_MESSAGE);
                // 关闭连接
                mcc.shutdown();
                return ;
            }
        }catch(Exception ex){
            System.out.println( ex.getMessage() );
        }
    }

    //向后追加数据
    private static void Append(String Key, String Value){
        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));
            //向后追加数据
            Future fo = mcc.append(Key, Value);

            boolean Ifin=false;
            //成功追加
            if(fo.get().toString().equals("true")){
                for(int i=0;i<content.size();i++){
                    String s=content.get(i).toString();
                    //在表格内
                    if (Key.equals(s.substring(1,s.indexOf(",")))){
                        row.add(Key); row.add((s.substring(s.indexOf(",")+2,s.length()-1)).concat(Value));
                        content.set(i,row.clone()); row.clear();
                        Ifin=true; break;
                    }
                }
                //不在表格内
                if(Ifin==false){
                    row.add(Key); row.add(mcc.get(Key).toString());
                    content.add(row.clone()); row.clear();
                }
                mcc.shutdown();
                model = new DefaultTableModel(content,title);
                return ;
            }
            //追加失败
            else{
                JOptionPane.showMessageDialog(null,"数据库中无目标Key", "追加错误",JOptionPane.ERROR_MESSAGE);
                // 关闭连接
                mcc.shutdown();
                return ;
            }
        }catch(Exception ex){
            System.out.println( ex.getMessage() );
        }
    }

    //删除数据
    private static void Delete(String Key){
        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));
            // 删除数据
            Future fo = mcc.delete(Key);

            //删除成功
            if(fo.get().toString().equals("true")){
                for(int i=0; i<content.size(); i++){
                    String s=content.get(i).toString();
                    //在表格内
                    if(s.substring(1,s.indexOf(",")).equals(Key)){
                        content.remove(i);
                        model = new DefaultTableModel(content,title);
                    }
                }
                JOptionPane.showMessageDialog(null,"删除"+Key+"成功", "删结果",JOptionPane.INFORMATION_MESSAGE);
            }
            //删除失败
            else{
                JOptionPane.showMessageDialog(null,"数据库中无目标Key", "删除错误",JOptionPane.ERROR_MESSAGE);
                // 关闭连接
                mcc.shutdown();
                return ;
            }
        }catch(Exception ex){
            System.out.println( ex.getMessage() );
        }
    }

    //自增
    private static void Inc(String Key, String Value){
        if(!isNumeric(Value)){
            JOptionPane.showMessageDialog(null,Value+"不为数字", "自增错误",JOptionPane.ERROR_MESSAGE);
            return;
        }

        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));

            //判断KEY是否存在
            if (GET(Key).equals("")) return;

            //判断Key是否对应为数
            if( !isNumeric(GET(Key))){
                JOptionPane.showMessageDialog(null,GET(Key)+"不为数字", "自增错误",JOptionPane.ERROR_MESSAGE);
                return;
            }

            //自增
            long goal=mcc.incr(Key,Integer.valueOf(Value).intValue());
            row.add(Key); row.add(goal);

            //开始判断是否在表格内
            boolean Ifin=false;
            for(int i=0;i<content.size();i++){
                String s=content.get(i).toString();
                //在表格内
                if (Key.equals(s.substring(1,s.indexOf(",")))){
                    row.add(Key); row.add(Value);
                    content.set(i,row.clone()); row.clear();
                    Ifin=true; break;
                }
            }
            //不在表格内
            if(Ifin==false){
                row.add(Key); row.add(Value);
                content.add(row.clone()); row.clear();
            }
            mcc.shutdown();
            model = new DefaultTableModel(content,title);
            return ;

        }catch(Exception ex){
            JOptionPane.showMessageDialog(null,"数据库中无目标Key", "自增错误",JOptionPane.ERROR_MESSAGE);
        }
    }

    //自减
    private static void Dec(String Key, String Value){
        if(!isNumeric(Value)){
            JOptionPane.showMessageDialog(null,Value+"不为数字", "自增错误",JOptionPane.ERROR_MESSAGE);
            return;
        }

        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));

            //判断KEY是否存在
            if (GET(Key).equals("")) return;

            //判断Key是否对应为数
            if( !isNumeric(GET(Key))){
                JOptionPane.showMessageDialog(null,GET(Key)+"不为数字", "自增错误",JOptionPane.ERROR_MESSAGE);
                return;
            }

            //自增
            long goal=mcc.decr(Key,Integer.valueOf(Value).intValue());
            row.add(Key); row.add(goal);

            //开始判断是否在表格内
            boolean Ifin=false;
            for(int i=0;i<content.size();i++){
                String s=content.get(i).toString();
                //在表格内
                if (Key.equals(s.substring(1,s.indexOf(",")))){
                    row.add(Key); row.add(Value);
                    content.set(i,row.clone()); row.clear();
                    Ifin=true; break;
                }
            }
            //不在表格内
            if(Ifin==false){
                row.add(Key); row.add(Value);
                content.add(row.clone()); row.clear();
            }
            mcc.shutdown();
            model = new DefaultTableModel(content,title);
            return ;

        }catch(Exception ex){
            JOptionPane.showMessageDialog(null,"数据库中无目标Key", "自增错误",JOptionPane.ERROR_MESSAGE);
        }
    }

    //从表格中删除数据
    private static void Drop(String Key){
        boolean Ifin=false;
        for(int i=0;i<content.size();i++){
            String s=content.get(i).toString();
            //在表格内
            if (Key.equals(s.substring(1,s.indexOf(",")))){
                content.remove(i);
                Ifin=true; break;
            }
        }
        //不在表格内
        if(Ifin==false){
            JOptionPane.showMessageDialog(null,"目标Key不在表格中", "删除错误",JOptionPane.ERROR_MESSAGE);
        }
        model = new DefaultTableModel(content,title);
        return ;
    }

    //判断是否为数
    private static boolean isNumeric(String str){
        for (int i = str.length();--i>=0;){
            if (!Character.isDigit(str.charAt(i))){
                return false;
            }
        }
        return true;
    }

    //获得数据
    private static String GET(String Key){
        String goal="";
        try{
            MemcachedClient mcc = new MemcachedClient(new InetSocketAddress("192.168.10.137", 11211));

            //查找数据
            if(!(mcc.get(Key).toString().equals("null"))){
                goal=mcc.get(Key).toString();
            }
        }catch(Exception ex){
            JOptionPane.showMessageDialog(null,"数据库中无目标Key", "查找错误",JOptionPane.ERROR_MESSAGE);
        }
        return goal;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("NoSQLPJ");
        frame.setContentPane(new NoSQLPJ().Panel1);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);

        title.add("Key"); title.add("Value");
        model = new DefaultTableModel(content,title);
    }
}
