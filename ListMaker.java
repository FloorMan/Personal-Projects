import java.util.Scanner;




public class ListMaker
{
	// This one is the example I made myself as practice.
	public int size;
	// Hard coded limit of 5 linked lists in the array
	public LinkedList [] arrayLists = new LinkedList[5];
	Scanner sc = new Scanner(System.in);
	
	
	public void createMenu()
	{
		int choice = 0;
		while(choice != -1)
		{
			listCommands();
			choice = sc.nextInt();
			System.out.println("--------------------------------------------------------");

			switch(choice)
			{
				case 0:
					System.out.println("You chose to exit the program. Goodbye!");
					choice = -1;
					break;
				case 1: 
					System.out.println("You chose to create a new list. Creating a list Right now!");
					createNewList();
					break;
				case 2: 
					System.out.println("You chose to delete an existing list!");
					deleteList();
					break;
				case 3: 
					System.out.println("You chose to modify an existing list!");
					modifyList();
					break;
				case 4:
					System.out.println("You chose to print a list!");
					printList();
					break;
				case 5: 
					System.out.println("You chose to nuke Uzbekistan, you monster. The international police will arrive shortly.");
					break;
				default:
					System.out.println("Please input a valid option.");
			}
			System.out.println("--------------------------------------------------------");
		}
	}
	
	
	public void createNewList()
	{
		if(size >= 5)
			System.out.println("Too many lists! Please delete one before making a new List!");
		else
		{
			LinkedList newList = new LinkedList();
			System.out.println("Give the node a value!");
			int value = sc.nextInt();
			
			newList.addNode(value);
			arrayLists[size++] = newList;
		}
	}
	
	public void deleteList()
	{
		int choice = 1;
		if (size == 0)
		{
			System.out.println("You need to make a list first in order to delete it dummy.");
			return;
		}
		if (size != 1)
			choice = chooseList("delete");
		
		for(int i=choice-1; i<size-1; i++)
		arrayLists[i] = arrayLists[i+1];
		arrayLists[size-1] = null;
		
		size--;
	}
	
	
	public void modifyList()
	{
		int choice = 1;
		if(size != 1)
			choice = chooseList("modify");
		
		int index=0;
		System.out.print("Add or delete a node: ");
		String choice2 = sc.next();
		
		switch (choice2)
		{
			case "add":
				System.out.println("There are currently " + arrayLists[choice-1].getSize() + " elements in this list."); 
				System.out.println("Please indicate at which index you would like to add a node. If you want to add to the end, then type -1");
				index = sc.nextInt();
				addNodeAtIndex(arrayLists[choice-1], index);
				break;
			case "Add":
				System.out.println("There are currently " + arrayLists[choice-1].getSize() + " elements in this list."); 
				System.out.println("Please indicate at which index you would like to add a node. If you want to add to the end, then type -1");
				index = sc.nextInt();
				addNodeAtIndex(arrayLists[choice-1], index);
				break;
			case "Delete":
				System.out.println("There are currently " + arrayLists[choice-1].getSize() + " elements in this list."); 
				System.out.println("Please indicate at which index you would like to delete a node.");
				index = sc.nextInt();
				deleteNodeAtIndex(arrayLists[choice-1],index);
				break;
			case "delete":
				System.out.println("There are currently " + arrayLists[choice-1].getSize() + " elements in this list."); 
				System.out.println("Please indicate at which index you would like to delete a node.");
				index = sc.nextInt();
				deleteNodeAtIndex(arrayLists[choice-1],index);
				break;
			default:
				System.out.println("Please type a valid choice");
		}
		
	}
	
	public void addNodeAtIndex(LinkedList n, int index)
	{
		if (index > n.getSize())
			index = n.getSize();
		
		System.out.print("Give the new node a value: ");
		int value = sc.nextInt();
		
		if(index <= 0)
			n.setHead(value);
		else			
			if(index == n.getSize())
				n.addNode(value);
			else
				n.insertNode(index, value);
	}
	
	public void deleteNodeAtIndex(LinkedList n, int index)
	{
		if (index >= n.getSize())
			index = n.getSize()-1;
		if (index < 0)
			index = 0;
		n.deleteNode(index);
	}
	
	public void printList()
	{
		int choice = 1;
		if (size == 0)
		{
			System.out.println("You need to make a list first inorder to print it dummy.");
			return;
		}
		if (size != 1)
			choice = chooseList("print");
		
		Node head = arrayLists[choice-1].getHead();	
		if (head == null)
			System.out.println("There are nodes in this list!");
		else 
		{
			while(head.nextGetter() != null)
			{
				System.out.print("| " + head.dataGetter() + " | -> ");
				head = head.nextGetter();
			}
			System.out.println("| " + head.dataGetter() + " |");
		}
	}
	
	public int chooseList(String action)
	{
		System.out.print("Select which list you would like to " + action + ": ");
			for(int i=1; i<=size; i++)
				System.out.print(i + ", ");
			System.out.println();
			
			int choice = sc.nextInt(); 
			while (choice > size || choice <= 0)
			{
				System.out.println("Please choose a valid list.");
				choice = sc.nextInt();
			}
			System.out.println("-------------------------------------");
		return choice;
	}
	
	
	
	public static void listCommands()
	{
		System.out.println("0) Exit the program.");
		System.out.println("1) Create a new list.");
		System.out.println("2) Delete an existing list.");
		System.out.println("3) Modify an existing list.");
		System.out.println("4) Print a list.");
		System.out.println("5) Nuke Uzbekistan.");
		System.out.println("--------------------------------------------------------");
	}
	
	
	
	
	
	public static void main(String [] args)
	{
		
		System.out.println("Welcome to the ListMaker3000 \u2122, please enter what you would like to do next");
		ListMaker w = new ListMaker();
		w.createMenu();
		//LinkedList first = new LinkedList();
		
		//first.addNode(12);
		
	}



}