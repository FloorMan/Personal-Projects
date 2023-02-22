public class Node
{
	private int data;
	private Node next;


	public Node(int value)
	{
		data = value;		
	}

	public Node nextGetter()
	{
		return next;
	}

	public int dataGetter()
	{
		return data;
	}

	public void setData(int value)
	{
		data = value;
	}

	public void setNext(Node n)
	{
		next = n;
	}

	
	
	
	
}