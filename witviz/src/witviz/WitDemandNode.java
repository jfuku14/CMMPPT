/*
 * Created on Nov 24, 2004
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package witviz;


/**
 * @author gresh
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class WitDemandNode extends WitNode {
	private String demandName;
	private String partName;
	
	public WitDemandNode() {
		super();


	}
	
	public String createKey() {
		
		String key = createKey(demandName, partName);
		return key;
	}
	public static String createKey(String d, String p){
		String key = d + " For: " +p;
        return key;
	}
	public String getDemandName() {
		return demandName;
	}
	public String getPartName() {
		return partName;
	}
	public void setDemandName(String d) {
		demandName = d;
		setText(d);
	}
	public void setPartName(String p) {
		partName =p;
	}
	public String getNiceName() {
		return "Demand: "+demandName +" for part: "+partName;
	}
	
}
