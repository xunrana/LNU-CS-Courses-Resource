package yuketangzuoye;

import java.util.Date;

public class Account 
{
	private int id=0;//账户id
	private double balance=0;//账户余额
	private static double rate=0;//（类变量）利率，所有账户利率相同
	private Date dateCreated;//账户创建日期
	
	//无参构造方法
	public Account(){
		this(0,0);//调用带参构造，默认id为0，余额为0
	}
	//指定id和余额的构造方法
	public Account(int id,double balance){
		this.id=id;//设置账户id
		this.balance=balance;//设置账户余额
		this.dateCreated=new Date();//获取当前日期作为账户创建日期
	}
	//获取账户id
	public int getId(){
		return id;
	}
	//设置账户id
	public void setId(int id){
		this.id=id;
	}
	//获取账户余额
	public double getBalance(){
		return balance;
	}
	//设置账户余额
	public void setBalance(double balance)
	{
		this.balance=balance;
	}
	//获取利率
	public static double getRate()
	{
		return rate;
	}
	//设置利率
	public static void setRate(double rate)
	{
		Account.rate=rate;
	}
	//获取账户创建日期
	public Date getDateCreated() {
		return dateCreated;
	}
	//获取月利息
	public double getMoneyInterest() {
		return balance*(rate/12);//余额*月利率
	}
	//取款
	public void withdraw(double amount)
	{
		balance-=amount;//余额减少
	}
	//存款
	public void deposit(double amount)
	{
		balance+=amount;//余额增加
	}
	//返回账户信息的字符串表示
	public String toString() {
		return "Account ID "+getId()+"\n"+
	           "Balance: $"+ getBalance()+"\n"+
	           "Date Created: "+getDateCreated();
	}
	
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub

	}
}