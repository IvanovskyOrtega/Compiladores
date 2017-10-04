import Data.*;

public class Parser extends SICParser {

     String[] rule1 = {"Arithmetic","Expression"};
     String[] rule2 = {"Expression","Expression","addOp","Term"};
     String[] rule3 = {"Expression","Term"};
     String[] rule4 = {"Term","Term","multOp","Factor"};
     String[] rule5 = {"Term","Factor"};
     String[] rule6 = {"Factor","openingBracket","Expression","closingBracket"};
     String[] rule7 = {"Factor","number"};
     String[] rule8 = {"Factor","name"};

     public Parser() {

          rule(1,rule1);
          rule(2,rule2);
          rule(3,rule3);
          rule(4,rule4);
          rule(5,rule5);
          rule(6,rule6);
          rule(7,rule7);
          rule(8,rule8);

          actionTable(1,"Term",SHIFT,12);
          actionTable(1,"Factor",SHIFT,10);
          actionTable(1,"name",SHIFT,2);
          actionTable(1,"openingBracket",SHIFT,4);
          actionTable(1,"Arithmetic",SHIFT,13);
          actionTable(1,"number",SHIFT,3);
          actionTable(1,"Expression",SHIFT,14);

          actionTable(2,"#",REDUCE,8);
          actionTable(2,"addOp",REDUCE,8);
          actionTable(2,"multOp",REDUCE,8);
          actionTable(2,"closingBracket",REDUCE,8);

          actionTable(3,"#",REDUCE,7);
          actionTable(3,"addOp",REDUCE,7);
          actionTable(3,"multOp",REDUCE,7);
          actionTable(3,"closingBracket",REDUCE,7);

          actionTable(4,"Term",SHIFT,12);
          actionTable(4,"Factor",SHIFT,10);
          actionTable(4,"name",SHIFT,2);
          actionTable(4,"openingBracket",SHIFT,4);
          actionTable(4,"number",SHIFT,3);
          actionTable(4,"Expression",SHIFT,5);

          actionTable(5,"addOp",SHIFT,6);
          actionTable(5,"closingBracket",SHIFT,11);

          actionTable(6,"Term",SHIFT,7);
          actionTable(6,"Factor",SHIFT,10);
          actionTable(6,"name",SHIFT,2);
          actionTable(6,"openingBracket",SHIFT,4);
          actionTable(6,"number",SHIFT,3);

          actionTable(7,"multOp",SHIFT,8);
          actionTable(7,"#",REDUCE,2);
          actionTable(7,"addOp",REDUCE,2);
          actionTable(7,"closingBracket",REDUCE,2);

          actionTable(8,"Factor",SHIFT,9);
          actionTable(8,"name",SHIFT,2);
          actionTable(8,"openingBracket",SHIFT,4);
          actionTable(8,"number",SHIFT,3);

          actionTable(9,"#",REDUCE,4);
          actionTable(9,"addOp",REDUCE,4);
          actionTable(9,"multOp",REDUCE,4);
          actionTable(9,"closingBracket",REDUCE,4);

          actionTable(10,"#",REDUCE,5);
          actionTable(10,"addOp",REDUCE,5);
          actionTable(10,"multOp",REDUCE,5);
          actionTable(10,"closingBracket",REDUCE,5);

          actionTable(11,"#",REDUCE,6);
          actionTable(11,"addOp",REDUCE,6);
          actionTable(11,"multOp",REDUCE,6);
          actionTable(11,"closingBracket",REDUCE,6);

          actionTable(12,"multOp",SHIFT,8);
          actionTable(12,"#",REDUCE,3);
          actionTable(12,"addOp",REDUCE,3);
          actionTable(12,"closingBracket",REDUCE,3);

          actionTable(13,"#",ACCEPT);

          actionTable(14,"addOp",SHIFT,6);
          actionTable(14,"#",REDUCE,1);

     }
}