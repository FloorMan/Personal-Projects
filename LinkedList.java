public class LinkedList
{
	private int size;
	private Node head;
	
	public Node getHead()
	{
		return head;
	}
	
	public int getSize()
	{
		return size;
	}
	
	private void addHead(int value)
	{
		head = new Node(value);
		size++;
	}
	
	public void setHead(int value)
	{
		Node temp = head;
		head = new Node(value);
		head.setNext(temp);
		size++;
	}
	
	public void setHead(Node newHead)
	{
		head = head.nextGetter();
	}
	
	
	// Made it a setter method so we can have restrictions
	public void addNode(int value)
	{
		this.setterAddNode(value);
	}
	
	public void insertNode(int index, int value)
	{
		Node newNode = head;
		for(int i = 0; i < index-1; i++)
			newNode = newNode.nextGetter();
		Node insertN = new Node(value);
		insertN.setNext(newNode.nextGetter());
		newNode.setNext(insertN);
		size++;
	}
	
	
	private void setterAddNode(int value)
	{
		if (size == 0)
			this.addHead(value);
		else
		{
			Node nextRef = head;
			// System.out.println("-----DEBUG: nextRef pointing at : " + nextRef.nextGetter() + "------");
			while (nextRef.nextGetter() != null)
				nextRef = nextRef.nextGetter();
			
			Node newNode = new Node(value);
			// System.out.println("-----DEBUG: nextRef pointing at : " + nextRef.nextGetter() + "------");
			nextRef.setNext(newNode);
			size++;
		}
	}
	
	public void deleteNode(int index)
	{
		
		if (size != 0)
		{
			Node position = head;
			if (index == 0)
				head = head.nextGetter();
			else
			{			
				for(int i = 0; i < index-1; i++)
					position = position.nextGetter();
				Node temp = position.nextGetter();
				position.setNext(temp.nextGetter());
			}
			size--;
		}
	}
	
}