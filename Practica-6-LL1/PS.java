package ll1;

import java.util.HashSet;
import java.util.Set;

public class PS {
    public char simbolo;
    public Set<Character> primeros = new HashSet<Character>();
    public Set<Character> siguientes = new HashSet<Character>();
    PS(){}
    PS(char simbolo, Set<Character> primeros){
        this.simbolo = simbolo;
        this.primeros = primeros;
    }
}
