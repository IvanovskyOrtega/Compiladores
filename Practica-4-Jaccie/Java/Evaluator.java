import Data.*;
import java.util.*;
import javax.swing.*;
@SuppressWarnings("unchecked")




public class Evaluator extends EvaluatorParallel {

    static String multOp(String op, String left, String right) {
      int a = 0, b = 1, c = 0, d = 1, index;
      index = left.indexOf("/");
      if (index == -1) a = Integer.parseInt(left);
      else {
        a = Integer.parseInt(left.substring(0,index));
        b = Integer.parseInt(left.substring(index+1));
      }
      index = right.indexOf("/");
      if (index == -1) c = Integer.parseInt(right);
      else {
        c = Integer.parseInt(right.substring(0,index));
        d = Integer.parseInt(right.substring(index+1));
      }
      if (op.equals("*")) {
        a = a*c;
        b = b*d; 
      }
      else {
        a = a*d;
        b = b*c;
      }
      //K�rzen
      if (b == 1) return ""+a;
      return kuerzen(a,b);
    }
    static String addOp(String op, String left, String right) {
      int a = 0,
          b = 1,
          c = 0,
          d = 1,
          index;
      index = left.indexOf("/");
      if (index == -1) a = Integer.parseInt(left);
      else {
        a = Integer.parseInt(left.substring(0,index));
        b = Integer.parseInt(left.substring(index+1));
      }
      index = right.indexOf("/");
      if (index == -1) c = Integer.parseInt(right);
      else {
        c = Integer.parseInt(right.substring(0,index));
        d = Integer.parseInt(right.substring(index+1));
      }
      if (op.equals("+")) {
        a = (a*d)+(b*c);
        b = b*d; 
      }
      else {
        a = (a*d)-(b*c);
        b = b*d; 
      }
      //K�rzen
      if (b == 1) return ""+a;
      return kuerzen(a,b);
    }
    static String kuerzen(int a, int b) {
      int i=2; 
      while (i<=b) {
        if ((a % i == 0) && (b % i == 0)) {
          a = a/i;
          b = b/i;
          i = 2;
        }
        else i++;
      }
      if (b == 1) return ""+a;
      else return ""+a+"/"+b;
    }

    protected void insertAttributes() {
        insertAttribute(this.tree,"Arithmetic","value");
        insertAttribute(this.tree,"Expression","variables");
        insertAttribute(this.tree,"Expression","value");
        insertAttribute(this.tree,"Expression","environment");
        insertAttribute(this.tree,"Term","variables");
        insertAttribute(this.tree,"Term","value");
        insertAttribute(this.tree,"Term","environment");
        insertAttribute(this.tree,"Factor","variables");
        insertAttribute(this.tree,"Factor","value");
        insertAttribute(this.tree,"Factor","environment");
    }

    protected void addAttributes() {
        addAttribute("value","0");
        addAttribute("variables","0");
        addAttribute("environment","1");
    }

    protected boolean checkIfPossible(String attr) {
        if (activeRule.equals("Arithmetic Expression")) {
            if (attr.equals("Arithmetic.value")) {
                return (check("Expression.value"));
            }
            else if (attr.equals("Expression.environment")) {
                return (check("Expression.variables"));
            }
            else return false;
        }
        else if (activeRule.equals("Expression1 Expression2 addOp Term")) {
            if (attr.equals("Expression1.variables")) {
                return (check("Expression2.variables") && 
                        check("Term.variables"));
            }
            else if (attr.equals("Expression1.value")) {
                return (check("Expression2.value") && 
                        check("addOp.string") && 
                        check("Term.value"));
            }
            else if (attr.equals("Expression2.environment")) {
                return (check("Expression1.environment"));
            }
            else if (attr.equals("Term.environment")) {
                return (check("Expression1.environment"));
            }
            else return false;
        }
        else if (activeRule.equals("Expression Term")) {
            if (attr.equals("Expression.variables")) {
                return (check("Term.variables"));
            }
            else if (attr.equals("Expression.value")) {
                return (check("Term.value"));
            }
            else if (attr.equals("Term.environment")) {
                return (check("Expression.environment"));
            }
            else return false;
        }
        else if (activeRule.equals("Term1 Term2 multOp Factor")) {
            if (attr.equals("Term1.variables")) {
                return (check("Term2.variables") && 
                        check("Factor.variables"));
            }
            else if (attr.equals("Term1.value")) {
                return (check("Term2.value") && 
                        check("multOp.string") && 
                        check("Factor.value"));
            }
            else if (attr.equals("Term2.environment")) {
                return (check("Term1.environment"));
            }
            else if (attr.equals("Factor.environment")) {
                return (check("Term1.environment"));
            }
            else return false;
        }
        else if (activeRule.equals("Term Factor")) {
            if (attr.equals("Term.variables")) {
                return (check("Factor.variables"));
            }
            else if (attr.equals("Term.value")) {
                return (check("Factor.value"));
            }
            else if (attr.equals("Factor.environment")) {
                return (check("Term.environment"));
            }
            else return false;
        }
        else if (activeRule.equals("Factor openingBracket Expression closingBracket")) {
            if (attr.equals("Factor.variables")) {
                return (check("Expression.variables"));
            }
            else if (attr.equals("Factor.value")) {
                return (check("Expression.value"));
            }
            else if (attr.equals("Expression.environment")) {
                return (check("Factor.environment"));
            }
            else return false;
        }
        else if (activeRule.equals("Factor number")) {
            if (attr.equals("Factor.variables")) {
                return true;
            }
            else if (attr.equals("Factor.value")) {
                return (check("number.string"));
            }
            else return false;
        }
        else if (activeRule.equals("Factor name")) {
            if (attr.equals("Factor.variables")) {
                return (check("name.string"));
            }
            else if (attr.equals("Factor.value")) {
                return (check("Factor.environment") && 
                        check("name.string"));
            }
            else return false;
        }
        else return false;
    }

    protected void calculate(String attr) {
        if (activeRule.equals("Arithmetic Expression")) {
            if (attr.equals("Arithmetic.value")) {
                String Arithmetic_value = null;
                String Expression_value = (String) get("Expression.value");
                Arithmetic_value = Expression_value;
                set("Arithmetic.value",Arithmetic_value);
            }
            else if (attr.equals("Expression.environment")) {
                HashMap<String,String> Expression_environment = null;
                HashSet<String> Expression_variables = (HashSet<String>) get("Expression.variables");
                Iterator<String> variablesIterator = Expression_variables.iterator();
                Expression_environment = new HashMap<String,String>();
                while (variablesIterator.hasNext()) {
                   String variableName = variablesIterator.next();
                   String inputValue = null;
                   boolean ok = false;
                   while (!ok) {
                     inputValue = JOptionPane.showInputDialog(
                       "Please input a value for " + variableName);
                     try{ 
                       Integer.parseInt(inputValue); 
                       ok=true;
                     } catch (Exception e) {ok = false;}
                   }
                   Expression_environment.put(variableName, inputValue);
                }
                set("Expression.environment",Expression_environment);
            }
        }
        else if (activeRule.equals("Expression1 Expression2 addOp Term")) {
            if (attr.equals("Expression1.variables")) {
                HashSet<String> Expression1_variables = null;
                HashSet<String> Expression2_variables = (HashSet<String>) get("Expression2.variables");
                HashSet<String> Term_variables = (HashSet<String>) get("Term.variables");
                Expression1_variables = new HashSet<String>();
                Expression1_variables.addAll(Term_variables);
                Expression1_variables.addAll(Expression2_variables);
                set("Expression1.variables",Expression1_variables);
            }
            else if (attr.equals("Expression1.value")) {
                String Expression1_value = null;
                String Expression2_value = (String) get("Expression2.value");
                String addOp_string = (String) get("addOp.string");
                String Term_value = (String) get("Term.value");
                Expression1_value = 
                   addOp(addOp_string, Expression2_value, Term_value);
                set("Expression1.value",Expression1_value);
            }
            else if (attr.equals("Expression2.environment")) {
                HashMap<String,String> Expression2_environment = null;
                HashMap<String,String> Expression1_environment = (HashMap<String,String>) get("Expression1.environment");
                Expression2_environment = Expression1_environment;
                set("Expression2.environment",Expression2_environment);
            }
            else if (attr.equals("Term.environment")) {
                HashMap<String,String> Term_environment = null;
                HashMap<String,String> Expression1_environment = (HashMap<String,String>) get("Expression1.environment");
                Term_environment = Expression1_environment;
                set("Term.environment",Term_environment);
            }
        }
        else if (activeRule.equals("Expression Term")) {
            if (attr.equals("Expression.variables")) {
                HashSet<String> Expression_variables = null;
                HashSet<String> Term_variables = (HashSet<String>) get("Term.variables");
                Expression_variables = Term_variables;
                set("Expression.variables",Expression_variables);
            }
            else if (attr.equals("Expression.value")) {
                String Expression_value = null;
                String Term_value = (String) get("Term.value");
                Expression_value = Term_value;
                set("Expression.value",Expression_value);
            }
            else if (attr.equals("Term.environment")) {
                HashMap<String,String> Term_environment = null;
                HashMap<String,String> Expression_environment = (HashMap<String,String>) get("Expression.environment");
                Term_environment = Expression_environment;
                set("Term.environment",Term_environment);
            }
        }
        else if (activeRule.equals("Term1 Term2 multOp Factor")) {
            if (attr.equals("Term1.variables")) {
                HashSet<String> Term1_variables = null;
                HashSet<String> Term2_variables = (HashSet<String>) get("Term2.variables");
                HashSet<String> Factor_variables = (HashSet<String>) get("Factor.variables");
                Term1_variables = new HashSet<String>();
                Term1_variables.addAll(Term2_variables);
                Term1_variables.addAll(Factor_variables);
                set("Term1.variables",Term1_variables);
            }
            else if (attr.equals("Term1.value")) {
                String Term1_value = null;
                String Term2_value = (String) get("Term2.value");
                String multOp_string = (String) get("multOp.string");
                String Factor_value = (String) get("Factor.value");
                Term1_value = 
                   multOp(multOp_string, Term2_value, Factor_value);
                set("Term1.value",Term1_value);
            }
            else if (attr.equals("Term2.environment")) {
                HashMap<String,String> Term2_environment = null;
                HashMap<String,String> Term1_environment = (HashMap<String,String>) get("Term1.environment");
                Term2_environment = Term1_environment;
                set("Term2.environment",Term2_environment);
            }
            else if (attr.equals("Factor.environment")) {
                HashMap<String,String> Factor_environment = null;
                HashMap<String,String> Term1_environment = (HashMap<String,String>) get("Term1.environment");
                Factor_environment = Term1_environment;
                set("Factor.environment",Factor_environment);
            }
        }
        else if (activeRule.equals("Term Factor")) {
            if (attr.equals("Term.variables")) {
                HashSet<String> Term_variables = null;
                HashSet<String> Factor_variables = (HashSet<String>) get("Factor.variables");
                Term_variables = Factor_variables;
                set("Term.variables",Term_variables);
            }
            else if (attr.equals("Term.value")) {
                String Term_value = null;
                String Factor_value = (String) get("Factor.value");
                Term_value = Factor_value;
                set("Term.value",Term_value);
            }
            else if (attr.equals("Factor.environment")) {
                HashMap<String,String> Factor_environment = null;
                HashMap<String,String> Term_environment = (HashMap<String,String>) get("Term.environment");
                Factor_environment = Term_environment;
                set("Factor.environment",Factor_environment);
            }
        }
        else if (activeRule.equals("Factor openingBracket Expression closingBracket")) {
            if (attr.equals("Factor.variables")) {
                HashSet<String> Factor_variables = null;
                HashSet<String> Expression_variables = (HashSet<String>) get("Expression.variables");
                Factor_variables = 
                  Expression_variables;
                set("Factor.variables",Factor_variables);
            }
            else if (attr.equals("Factor.value")) {
                String Factor_value = null;
                String Expression_value = (String) get("Expression.value");
                Factor_value = Expression_value;
                set("Factor.value",Factor_value);
            }
            else if (attr.equals("Expression.environment")) {
                HashMap<String,String> Expression_environment = null;
                HashMap<String,String> Factor_environment = (HashMap<String,String>) get("Factor.environment");
                Expression_environment = Factor_environment;
                set("Expression.environment",Expression_environment);
            }
        }
        else if (activeRule.equals("Factor number")) {
            if (attr.equals("Factor.variables")) {
                HashSet<String> Factor_variables = null;
                Factor_variables = new HashSet<String>();
                set("Factor.variables",Factor_variables);
            }
            else if (attr.equals("Factor.value")) {
                String Factor_value = null;
                String number_string = (String) get("number.string");
                Factor_value = number_string;
                set("Factor.value",Factor_value);
            }
        }
        else if (activeRule.equals("Factor name")) {
            if (attr.equals("Factor.variables")) {
                HashSet<String> Factor_variables = null;
                String name_string = (String) get("name.string");
                Factor_variables = new HashSet<String>();
                Factor_variables.add(name_string);
                set("Factor.variables",Factor_variables);
            }
            else if (attr.equals("Factor.value")) {
                String Factor_value = null;
                HashMap<String,String> Factor_environment = (HashMap<String,String>) get("Factor.environment");
                String name_string = (String) get("name.string");
                Factor_value = Factor_environment.get(name_string);
                set("Factor.value",Factor_value);
            }
        }
    }

}
