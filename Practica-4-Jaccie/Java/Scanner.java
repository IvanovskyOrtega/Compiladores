import Data.*;

public class Scanner extends ScannerScanner {

     public Scanner() {
     super("Scanner",new ScannerInput());

     ScannerInput input = super.getScannerInput();
     String[][] verbatims = new String[2][2];
     verbatims[0][0] = "<";
     verbatims[0][1] = ">";
     verbatims[1][0] = "!";
     verbatims[1][1] = "!";
     input.setVerbatims(verbatims);
     String[][] comments = new String[2][2];
     comments[0][0] = "--";
     comments[0][1] = "JACCIE_EndOfLine";
     comments[1][0] = "/*";
     comments[1][1] = "*/";
     input.setComments(comments);

     Automat automat;
     Transition transition;
     State state;

          automat = new Automat("JACCIE_Separators");
          state= new State(0,".Separators",false);
          state.add(new Transition("9-10,12-13,32",1));
          automat.add(state);
          state= new State(1,"Separators.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("JACCIE_Strings");
          state= new State(0,"(.#34)",false);
          state.add(new Transition("34",1));
          automat.add(state);
          state= new State(1,"(#34).",true);
          automat.add(state);
          add(automat);

          automat = new Automat("JACCIE_Comments");
          state= new State(0,"(.--|./*)",false);
          state.add(new Transition("47",2));
          state.add(new Transition("45",1));
          automat.add(state);
          state= new State(1,"(-.-|/*)",false);
          state.add(new Transition("45",3));
          automat.add(state);
          state= new State(2,"(--|/.*)",false);
          state.add(new Transition("42",3));
          automat.add(state);
          state= new State(3,"(--|/*).",true);
          automat.add(state);
          add(automat);

          automat = new Automat("JACCIE_Verbatims");
          state= new State(0,"(.<|.!)",false);
          state.add(new Transition("33,60",1));
          automat.add(state);
          state= new State(1,"(<|!).",true);
          automat.add(state);
          add(automat);

          automat = new Automat("addOp");
          state= new State(0,"(.+|.-)",false);
          state.add(new Transition("43,45",1));
          automat.add(state);
          state= new State(1,"(+|-).",true);
          automat.add(state);
          add(automat);

          automat = new Automat("multOp");
          state= new State(0,"(.*|./)",false);
          state.add(new Transition("42,47",1));
          automat.add(state);
          state= new State(1,"(*|/).",true);
          automat.add(state);
          add(automat);

          automat = new Automat("openingBracket");
          state= new State(0,".(",false);
          state.add(new Transition("40",1));
          automat.add(state);
          state= new State(1,"(.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("closingBracket");
          state= new State(0,".)",false);
          state.add(new Transition("41",1));
          automat.add(state);
          state= new State(1,").",true);
          automat.add(state);
          add(automat);

          automat = new Automat("name");
          state= new State(0,"(.{a-z}|.{A-Z})(({a-z}|{A-Z})|{0-9})[0-*]",false);
          state.add(new Transition("65-90,97-122",1));
          automat.add(state);
          state= new State(1,"({a-z}|{A-Z})((.{a-z}|.{A-Z})|.{0-9})[0-*].",true);
          state.add(new Transition("48-57,65-90,97-122",2));
          automat.add(state);
          state= new State(2,"({a-z}|{A-Z})@(({a-z}|{A-Z})|{0-9})[0-*]@",false);
          state.setInternState(true);
          state.setLoops(0,0);
          state.setEndlessLoop(true);
          state.setFollowState(0,0);
          state.setFollowState(2,1);
          automat.add(state);
          add(automat);

          automat = new Automat("number");
          state= new State(0,".{0-9}[1-*]",false);
          state.add(new Transition("48-57",1));
          automat.add(state);
          state= new State(1,"@{0-9}[1-*]@",false);
          state.setInternState(true);
          state.setLoops(0,0);
          state.setEndlessLoop(true);
          state.setFollowState(0,0);
          state.setFollowState(2,2);
          automat.add(state);
          state= new State(2,".{0-9}[1-*].",true);
          state.add(new Transition("48-57",1));
          automat.add(state);
          add(automat);

     } // End of constructor

} // End of class Scanner


