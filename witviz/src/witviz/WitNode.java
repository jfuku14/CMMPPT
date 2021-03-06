/*
 * Created on Nov 24, 2004
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package witviz;



import org.eclipse.draw2d.ChopboxAnchor;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;

/**
 * @author gresh
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class WitNode extends Label {
	private  String nodeType;
	//private  String internalName;
	public ChopboxAnchor topAnchor;
	public ChopboxAnchor bottomAnchor;
	public WitNode() {
		super();
		this.setTextAlignment(TOP);
		this.setTextPlacement(SOUTH);
		this.setBorder(new LineBorder()); //default of one pixel

	}
	public String getNodeType() {
		return nodeType;		
	}
	public void setNodeType(String t) {
		nodeType = t;
	}
	public void setText(String t) {
		super.setText(t);
		//internalName=t;
	}
	//public void setInternalName(String t) {
		//internalName=t;
	//}
	//public String getInternalName() {
	//	return internalName;
	//}
	public  String createKey() {
		
		String key = createKey(nodeType, getText());
		return key;
	}
	public static String createKey(String type, String name){
		String key = "NodeType: "+ type + " Name: " +name;
        return key;
	}
	public String getNiceName() {
		return createKey();
	}

}
