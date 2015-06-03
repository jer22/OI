public class Time{
	public String whatTime(int second) {
		int hour = second / 3600;
		second %= 3600;
		int minute = second / 60;
		second %= 60;
		String s = Integer.toString(hour) + ":" + Integer.toString(minute) + ":" + Integer.toString(second);

		return s;
	}
}