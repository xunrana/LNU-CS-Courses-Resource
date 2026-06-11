package yuketangzuoye;
import java.util.Scanner;
public class Location {
	public int row;//行
	public int column;//列
	public double maxValue;//最大值
	//构造方法，用于初始化对象
	public Location(int row,int column,double maxValue)
	{
		this.row=row;
		this.column=column;
		this.maxValue=maxValue;
	}
	//静态方法，返回二维数组中最大值的信息
	public static Location LocateLargest(double[][]a) {
		Location location=new Location(0,0,a[0][0]);//初始化位置信息
		//遍历二维数组，寻找最大值位置
		for(int i=0;i<a.length;i++)
		{
			for(int j=0;j<a[i].length;j++)
			{
				if(a[i][j]>location.maxValue)//当前位置大于已知最大值
				{
					location.maxValue=a[i][j];//更新最大值
					location.row=i;//更新行位置
					location.column=j;//更新列位置
				}
			}
		}
		return location;//返回最大值位置信息
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("请输入二维数组的行数和列数：");
		Scanner input=new Scanner(System.in);
		int rows=input.nextInt();//读入行数
		int columns=input.nextInt();//读入列数
		double[][] array=new double[rows][columns];//创建二维数组
		
		System.out.println("请输入二维数组的元素:");
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<columns;j++)
			{
				array[i][j]=input.nextDouble();//逐个读取二维数组
			}
		}
		Location loc=LocateLargest(array);//获取最大元素位置信息
		System.out.println("数组中最大的元素为 "+loc.maxValue
				+"，位于位置（"+loc.row+", "+loc.column+")");
		
	}

}
