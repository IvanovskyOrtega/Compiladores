import Data.*;

public class Scanner extends ScannerScanner {

     public Scanner() {
     super("Scanner",new ScannerInput());

     ScannerInput input = super.getScannerInput();
     String[][] comments = new String[1][2];
     comments[0][0] = "/*";
     comments[0][1] = "*/";
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
          state= new State(0,"(./*)",false);
          state.add(new Transition("47",1));
          automat.add(state);
          state= new State(1,"(/.*)",false);
          state.add(new Transition("42",2));
          automat.add(state);
          state= new State(2,"(/*).",true);
          automat.add(state);
          add(automat);

          automat = new Automat("v");
          state= new State(0,".var",false);
          state.add(new Transition("118",1));
          automat.add(state);
          state= new State(1,"v.ar",false);
          state.add(new Transition("97",2));
          automat.add(state);
          state= new State(2,"va.r",false);
          state.add(new Transition("114",3));
          automat.add(state);
          state= new State(3,"var.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("a");
          state= new State(0,".{a-z}[1-*]",false);
          state.add(new Transition("97-122",1));
          automat.add(state);
          state= new State(1,"@{a-z}[1-*]@",false);
          state.setInternState(true);
          state.setLoops(0,0);
          state.setEndlessLoop(true);
          state.setFollowState(0,0);
          state.setFollowState(2,2);
          automat.add(state);
          state= new State(2,".{a-z}[1-*].",true);
          state.add(new Transition("97-122",1));
          automat.add(state);
          add(automat);

          automat = new Automat("z");
          state= new State(0,".;",false);
          state.add(new Transition("59",1));
          automat.add(state);
          state= new State(1,";.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("s");
          state= new State(0,".+",false);
          state.add(new Transition("43",1));
          automat.add(state);
          state= new State(1,"+.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("r");
          state= new State(0,".-",false);
          state.add(new Transition("45",1));
          automat.add(state);
          state= new State(1,"-.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("p");
          state= new State(0,".(",false);
          state.add(new Transition("40",1));
          automat.add(state);
          state= new State(1,"(.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("q");
          state= new State(0,".)",false);
          state.add(new Transition("41",1));
          automat.add(state);
          state= new State(1,").",true);
          automat.add(state);
          add(automat);

          automat = new Automat("c");
          state= new State(0,".,",false);
          state.add(new Transition("44",1));
          automat.add(state);
          state= new State(1,",.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("n");
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

          automat = new Automat("i");
          state= new State(0,".if",false);
          state.add(new Transition("105",1));
          automat.add(state);
          state= new State(1,"i.f",false);
          state.add(new Transition("102",2));
          automat.add(state);
          state= new State(2,"if.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("w");
          state= new State(0,".while",false);
          state.add(new Transition("119",1));
          automat.add(state);
          state= new State(1,"w.hile",false);
          state.add(new Transition("104",2));
          automat.add(state);
          state= new State(2,"wh.ile",false);
          state.add(new Transition("105",3));
          automat.add(state);
          state= new State(3,"whi.le",false);
          state.add(new Transition("108",4));
          automat.add(state);
          state= new State(4,"whil.e",false);
          state.add(new Transition("101",5));
          automat.add(state);
          state= new State(5,"while.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("g");
          state= new State(0,".>",false);
          state.add(new Transition("62",1));
          automat.add(state);
          state= new State(1,">.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("l");
          state= new State(0,".<",false);
          state.add(new Transition("60",1));
          automat.add(state);
          state= new State(1,"<.",true);
          automat.add(state);
          add(automat);

          automat = new Automat("e");
          state= new State(0,".=",false);
          state.add(new Transition("61",1));
          automat.add(state);
          state= new State(1,"=.",true);
          automat.add(state);
          add(automat);

     } // End of constructor

} // End of class Scanner
