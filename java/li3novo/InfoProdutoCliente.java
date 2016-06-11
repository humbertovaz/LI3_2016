/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 

import java.util.Arrays;

/**
 *
 *
 */
public class InfoProdutoCliente {
    private int [] quantidade; // [12] mes
    private int quantidadeTotal;
    private double [] faturado; // [12] mes
    private double totalFaturado;
    private int[] compras;

   

    
    public InfoProdutoCliente(){
        this.quantidadeTotal=0;
        this.totalFaturado=0;
         this.quantidade=new int[12];
        this.faturado=new double[12];
        this.compras=new int[12];
        for(int i=0;i<12;i++){
                faturado[i]=0;
                quantidade[i]=0;
                compras[i]=0;
        }
    }
    public InfoProdutoCliente(int[] quantidade, double[] faturado, double totalFaturado,int quantidadeTotal, int []compras) {
        this.quantidadeTotal = quantidadeTotal;
        this.totalFaturado = totalFaturado;
         this.quantidade=new int[12];
        this.faturado=new double[12];
        this.compras=new int[12];
        for(int i=0;i<12;i++){
                this.quantidade[i]=quantidade[i];
                this.faturado[i]=faturado[i];
                this.compras[i]=compras[i];
        }
    }
    public InfoProdutoCliente (InfoProdutoCliente o){
        this.quantidadeTotal=o.getQuantidadeTotal();
        this.totalFaturado=o.getTotalFaturado();
        this.faturado=o.getFaturado();
        this.quantidade=o.getQuantidade();
        this.compras=o.getcompras();
    }

    public int[] getcompras(){
        int[] res= new int[12];
        for(int i=0;i<12;i++){
                res[i]=this.compras[i];
        }
        return res;
    }

    public int getQuantidadeTotal() {
        return this.quantidadeTotal;
    }

    public double getTotalFaturado() {
        return totalFaturado;
    }

    public double[] getFaturado(){
        double fat[]=new double[12];
        for(int i=0;i<12;i++){
                fat[i]=this.faturado[i];
        }
        return fat;
    }
    
    
    public double getFaturadoMes(int mes){
        return this.faturado[mes-1];
    }
    
    public int getComprasMes(int mes){
        return this.compras[mes-1];
    }
    
    public int[] getQuantidade(){
        int quant[]=new int[12];
        for(int i=0;i<12;i++){
            quant[i]=this.quantidade[i];
        }
        return quant;
    }
    
    public void setcompras(int []v){
        for(int i=0;i<12;i++){
            this.compras[i]=v[i];
        }
    }

    public void setQuantidadeMesPorFilial(int[] quantidade) {
        for(int i=0;i<12;i++){
                this.quantidade[i]=quantidade[i];
        }
    }

    public void setTotalGasto(double[] faturado) {
        for(int i=0;i<12;i++){
                this.faturado[i]=faturado[i];
        }
    }
    
    public boolean comprado(){
        return (this.quantidadeTotal>0);
    }

    
    public boolean compradoMes(int mes){
        return quantidade[mes]>0;
    }
    
    public InfoProdutoCliente clone(){
        return new InfoProdutoCliente(this);
    }

    @Override
    public String toString() {
        return "InfoProdutoCliente{" +  ", quantidadeMesPorFilial=" + Arrays.toString(quantidade) + ", totalGasto=" + Arrays.toString(faturado) + '}';
    }

    

    
    
    
    
    
    
    
    public void inser(int mes,int quantidade,double faturado) {
    
        this.compras[mes]++;
        this.quantidade[mes]+=quantidade;
        this.quantidadeTotal+=quantidade;
        this.totalFaturado+=faturado;
        this.faturado[mes]+=faturado;
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
        final InfoProdutoCliente other = (InfoProdutoCliente) obj;
        if (this.quantidadeTotal != other.getQuantidadeTotal()) {
            return false;
        }
        if (Double.doubleToLongBits(this.totalFaturado) != Double.doubleToLongBits(other.getTotalFaturado())) {
            return false;
        }
        if (!Arrays.equals(this.quantidade, other.getQuantidade())) {
            return false;
        }
        if (!Arrays.equals(this.faturado, other.getFaturado())) {
            return false;
        }
        if (!Arrays.equals(this.compras, other.getCompras())) {
            return false;
        }
        return true;
    }
    
    
    
    
    public int [] getCompras() {
    int [] a = new int [12];
    
        System.arraycopy(this.compras, 0, a, 0, 12);
    
    return a;
  }
    
     public void setQuantidadeTotal(int quantidadeTotal) {
        this.quantidadeTotal = quantidadeTotal;
    }

    public void setTotalFaturado(double totalFaturado) {
        this.totalFaturado = totalFaturado;
    }
    
    
    
    
    
    
    
    
    
}
