 
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * 
 */
public class ComparatorProdutoQuantidade {
    
    public int compare(InfoProduto p1, InfoProduto p2) {
        return p1.getProduto().compareTo(p2.getProduto());
    }
}
