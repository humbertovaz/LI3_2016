/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 

import java.util.Comparator;

/**
 *
 * 
 */
public class ComparatorClientePorCodigo implements Comparator<Cliente> {

    

    @Override
    public int compare(Cliente c1, Cliente c2) {
        return c1.getCodigoCliente().compareTo(c2.getCodigoCliente());
    }

}
