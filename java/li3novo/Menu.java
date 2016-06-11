

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author gil
 */
public class Menu implements Serializable{
    
    
    
     // variaveis de instancia
    private List<String> opcoes;
    private int op;
  
    
    /**
     * Constructor for objects of class Menu
     * @param opcoes
     */
    public Menu(String[] opcoes) {
        this.opcoes = new ArrayList<>();
        this.opcoes.addAll(Arrays.asList(opcoes)); //(int i=0; i<opcoes.length; i++)
        this.op = 0;
    }

    /**
     * apresenta o menu e le uma opcao
     */
    public void executa() {
        do {
            showMenu();
            this.op = lerOpcao();
            
        } while (this.op == -1);
    }
    
    /**
     * Apresentar o menu
     */
    private void showMenu() {
        System.out.println("\n *** Menu *** ");
        for (int i=0; i<this.opcoes.size(); i++) {
            System.out.print(i+1);
            System.out.print("  - ");
            System.out.println(this.opcoes.get(i));
        }
        System.out.println("0  - Sair");
    }
    
    /**
     * Ler uma opcao vaida
     */
    private int lerOpcao() {
        
        int opcao; 
        System.out.print("Opcao: ");
        opcao = Input.lerInt(); 
        if (opcao<0 || opcao>this.opcoes.size()) {
            System.out.println("Opcao Invalida!!!");
            opcao = -1;
        }
        return opcao;
    }
    
    /**
     * Opcao lida
     * @return 
     */
    public int getOpcao() {
        return this.op;
    }
}