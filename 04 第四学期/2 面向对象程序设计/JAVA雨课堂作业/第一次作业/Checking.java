package yuketangzuoye;

public class Checking extends Account {
	protected double overdraftLimit;//透支限定额
	
	//构造方法，初始化账户名、余额、透支限定额
	public Checking(int id,double balance,double overdraftLimit)
	{
		super(id,balance);//调用父类的构造方法
		this.overdraftLimit=overdraftLimit;//初始化透支限定额
	}
	//获取透支限定额
	public double getOverdraftLimit() {
		return overdraftLimit;
	}
	//设置透支限定额
	public void setOverdraftLimit(double overdraftLimit) {
		this.overdraftLimit=overdraftLimit;
	}
	//返回账户信息的字符串表示
	public String toString() {
		return "Checking Account ID: "+getId()+"\n"+
	           "Balance:$ "+getBalance()+"\n"+
			   "Overdraft Limit: $"+getOverdraftLimit()+"\n"+
	           "Date Created: "+getDateCreated();
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//创建一个Checking账户对象，初始余额为1000，透支限定额为500
		Checking checkingAccount=new Checking(1,1000,500);
		//设置利率为0.03
		Account.setRate(0.03);
		//存款500
		checkingAccount.deposit(500);
		//获取余额
		System.out.println(checkingAccount.getBalance());
		//取款2000
		checkingAccount.withdraw(2000);
		//获取余额
		System.out.println(checkingAccount.getBalance());
		//打印月利率
		System.out.println("Monthly Interest: $"+checkingAccount.getMoneyInterest());
		//打印账户信息
		System.out.println(checkingAccount.toString());
	}

}
