package yuketangzuoye;

public class Utility {
	public static <T extends Comparable<T>> T max(T obj1,T obj2) {
		if(obj1.compareTo(obj2)>0) {
			return obj1;
		}else {
		return obj2;	
		}
	}

}
