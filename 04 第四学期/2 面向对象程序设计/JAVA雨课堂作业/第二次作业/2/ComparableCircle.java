package yuketangzuoye;

public class ComparableCircle extends Circle implements Comparable<ComparableCircle>{
	public ComparableCircle(double radius) {
		super(radius);
	}
	public int compareTo(ComparableCircle other) {
		if(this.getArea()>other.getArea()) {
			return 1;
		}else if(this.getArea()<other.getArea()) {
			return -1;
		}
		else {
			return 0;
		}
	}
	public String toString()
	{
		return "Circle with radius: "+getRadius()+"\nand area "+getArea();
	}
}
