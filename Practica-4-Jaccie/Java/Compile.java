import Data.*;
import java.util.*;

public class Compile extends Observable
              implements CompilerAction, Runnable {

    private String input = "";

    public void setInput(Object o) {
        inputTree = null;
        input = (String)o;
    }

    public void run() {
        Scanner scanner =  new Scanner();
        scanner.getScannerInput().setInput(input);
        try {
            System.out.println("/********************************/");
            System.out.println("Inicia análisis léxico...\n");
            scanner.resetScanner();
            scanner.scanAll();
            System.out.println(scanner.getResultAsString());
        } catch (Exception e) {
             update("Error while scanning: "+
                    e.toString());
        }
        System.out.println("Termina análisis léxico...");
        System.out.println("/********************************/\n");
        update("Scanner finished.");
        System.out.println("/********************************/");
        System.out.println("Inicia Parseo...\n");

        SICParserInput pinput = new SICParserInput();
        Vector scannerResult = scanner.getResult();

        for (int i=0; i<scannerResult.size(); i++)
            pinput.addScannerOutput((String)
                scannerResult.elementAt(i));
        Parser parser =  new Parser();
        parser.start(pinput);
        System.out.println(parser.getResultAsString());
        update("Parser finished.");
        System.out.println("Termina parseo...");
        System.out.println("/********************************/\n");
        einput = parser.getResultAsString();
        Evaluator evaluator = new Evaluator();
        if (inputTree == null) evaluator.setTree(einput);
            else evaluator.setTree(inputTree);
        evaluator.start();
        inputTree = evaluator.getTree();
        update("Evaluator finished.");

        update("Finished.");
    }

    public Object getResult() {
        return inputTree;
    }

    private EvaluatorTree inputTree = null;
    private String einput = "";

    private Observer observer = null;

    public void setObserver(Observer o) {
         observer = o;
    }

    private void update(String message) {
        if (observer != null) observer.update(this,message);
    }
}