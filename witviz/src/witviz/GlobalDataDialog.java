/*
 * Created on Jan 7, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package witviz;



import org.eclipse.draw2d.ColorConstants;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.StyledText;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;

/**
 * @author gresh
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class GlobalDataDialog extends Dialog {

    final Shell shell;
    org.eclipse.swt.graphics.Color HighlightColor = ColorConstants.yellow;
    Shell parent;
    StyledText textBox;   
    WitObject wo;
    SimpleTree parentApp;
    boolean isOpen=false;
	/**
	 * @param parent
	 */
	public GlobalDataDialog(Shell parent, SimpleTree p) {
		super(parent);
	    shell= new Shell(parent, SWT.DIALOG_TRIM | SWT.MODELESS | SWT.RESIZE);
        parentApp = p;

		// TODO Auto-generated constructor stub
		initializeShell();
	}

	/**
	 * @param parent
	 * @param style
	 */

    public void setWitObject(WitObject witobject) {
		wo=witobject;    	
    }   
	public void initializeShell() {

		parent = getParent();
		shell.setText("Global Data");
		
		
	
	    GridLayout gridLayout1 = new GridLayout();
	    gridLayout1.numColumns = 1;
	    shell.setLayout(new FormLayout());
	    
	    FormData fd1 = new FormData();
	    fd1.top = new FormAttachment(0,5);
	    fd1.left = new FormAttachment(0,5);
	    fd1.right = new FormAttachment(100,-5);
	    fd1.bottom = new FormAttachment(100,-5);
	    
		textBox = new StyledText (shell, SWT.LEAD|SWT.MULTI|SWT.WRAP|SWT.H_SCROLL|SWT.V_SCROLL|SWT.BORDER);
		textBox.setText (" ");
		

		textBox.setLayoutData(fd1);
		

		//final Button ok = new Button (composite, SWT.PUSH);
		//ok.setText ("Ok");
		//Button cancel = new Button (composite, SWT.PUSH);
		//cancel.setText ("Cancel");
		//Listener listener =new Listener () {
		//	public void handleEvent (Event event) {
				//result [0] = event.widget == ok;
		//	
			//}
		//};
		//ok.addListener (SWT.Selection, listener);
		shell.addListener(SWT.Close, new Listener(){
			   public void handleEvent(Event event) {
			       event.doit=false;
			       close();
			       //your code here

			    }
			   });	 
		
		shell.pack ();
		shell.setSize(300,400);

		shell.setVisible(false);
	}
	public void open () {
		shell.setVisible(true);
		int numparts = wo.getNumParts();
		int numoperations = wo.getNumOperations();
		GlobalOptionsDialog globalOptionsDialog = parentApp.globalOptionDialog;
		textBox.setText("Number of Parts: "+ numparts + "\n");
		textBox.append("Number of Operations: "+ numoperations + "\n");
      
		if (wo.getStochMode()) {
			int currentScenario=wo.getCurrentScenario();
			String currentScenarioString = "Current Scenario: "+currentScenario+"\n";
			textBox.append(currentScenarioString);
		}
		if (wo.getMultObjectiveMode()) {
			String currentObjective=wo.getCurrentObjective();
			String currentObjectiveString = "Current Objective: "+currentObjective+"\n";
			textBox.append(currentObjectiveString);
		}

		globalOptionsDialog.getOptionsString(textBox);
		Display display = parent.getDisplay();
		isOpen=true;
		
		

	}
	public void close() {
		//just make invisible
		shell.setVisible(false);
		isOpen=false;
	}

}
