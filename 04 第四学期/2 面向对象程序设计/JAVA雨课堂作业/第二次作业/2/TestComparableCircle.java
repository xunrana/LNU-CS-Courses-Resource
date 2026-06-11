package yuketangzuoye;

public class TestComparableCircle {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ComparableCircle circle1=new ComparableCircle(5.0);
		ComparableCircle circle2=new ComparableCircle(4.0);
		ComparableCircle largerCircle=Utility.max(circle1, circle2);
		System.out.println("Larger Circle: "+largerCircle);
	}
}
