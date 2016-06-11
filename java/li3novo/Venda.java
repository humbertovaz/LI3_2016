/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 

import java.io.Serializable;
import java.util.Objects;

public class Venda implements Serializable{

  private String codigoProduto;
   private String codigoCliente;
   private char modoDeCompra;
   private int mes;
   private int filial;
   private double preco;
   private int quantidade;
   
public Venda(String codigoProduto, String codigoCliente, char modoDeCompra, int mes, int filial, double preco,int quantidade) {
        this.codigoProduto = codigoProduto;
        this.codigoCliente = codigoCliente;
        this.modoDeCompra=modoDeCompra;
        this.mes = mes;
        this.filial = filial;
        this.preco = preco;
        this.quantidade=quantidade;
    }

    public Venda() {
        this.codigoCliente="";
        this.codigoProduto="";
        this.modoDeCompra=' ';
        this.mes = -1;
        this.filial = 0;
        this.preco = -1;
        this.preco = 0.0;
        this.quantidade=0;
    }
    
    public Venda (Venda v){
        this.codigoProduto = v.getCodigoProduto();
        this.codigoCliente = v.getCodigoCliente();
        this.modoDeCompra=v.getModoDeCompra();
        this.mes = v.getMes();
        this.filial = v.getFilial();
        this.preco = v.getPreco();
        this.quantidade=v.getQuantidade();
    }
    
   public char getModoDeCompra() {
        return modoDeCompra;
    }

    public String getCodigoProduto() {
        return codigoProduto;
    }

    public String getCodigoCliente() {
        return this.codigoCliente;
    }

    public int getMes() {
        return mes;
    }

    public int getFilial() {
        return filial;
    }

    public double getPreco() {
        return preco;
    }

public int getQuantidade() {
        return quantidade;
    }

    @Override
    public boolean equals(Object obj) {

       if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Venda other = (Venda) obj;
        if (this.modoDeCompra != other.getModoDeCompra()) {
            return false;
        }
        if (this.mes != other.getMes()) {
            return false;
        }
        if (this.filial != other.getFilial()) {
            return false;
        }
        if (Double.doubleToLongBits(this.preco) != Double.doubleToLongBits(other.getPreco())) {
            return false;
        }
        if (!Objects.equals(this.codigoProduto, other.getCodigoProduto())) {
            return false;
        }
        if (!Objects.equals(this.codigoCliente, other.getCodigoCliente())) {
            return false;
        }
        if (this.quantidade != other.getQuantidade()) {
            return false;
        }
      

        return true;
    
    }

   

    
    
    @Override
    public String toString() {
        return "Venda{" + "codigoProduto=" + codigoProduto + ", codigoCliente=" + codigoCliente + ", modoDeCompra=" + modoDeCompra + ", mes=" + mes + ", filial=" + filial + ", preco=" + preco + '}';
    }

     
      
    
   @Override
    public Venda clone (){
        return new Venda(this);
    }

    public void setCodigoProduto(String codigoProduto) {
        this.codigoProduto = codigoProduto;
    }

    public void setCodigoCliente(String codigoCliente) {
        this.codigoCliente = codigoCliente;
    }

    public void setModoDeCompra(char modoDeCompra) {
        this.modoDeCompra = modoDeCompra;
    }

    public void setMes(int mes) {
        this.mes = mes;
    }

    public void setFilial(int filial) {
        this.filial = filial;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }


    public void setQuantidade(int quantidade) {
        this.quantidade = quantidade;
    }
    
}