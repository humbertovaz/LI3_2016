/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 

import java.io.Serializable;
import java.util.Comparator;

/**
 *
 *
 */
public class ComparatorProdutoPorCodigo implements Comparator<Produto> ,Serializable {

    

    @Override
    public int compare(Produto p1, Produto p2) {
        return p1.getCodigoProduto().compareTo(p2.getCodigoProduto());
    }

}