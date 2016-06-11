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
        for(int i=0;i<12;i++){
                faturado[i]=0;
                quantidade[i]=0;
                compras[i]=0;
        }
    }
    public InfoProdutoCliente(int[] quantidade, double[] faturado, double totalFaturado,int quantidadeTotal, int []compras) {
        this.quantidadeTotal = quantidadeTotal;
        this.totalFaturado = totalFaturado;
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
        return quantidade[mes-1]>0;
    }
    
    public InfoProdutoCliente clone(){
        return new InfoProdutoCliente(this);
    }

    @Override
    public String toString() {
        return "InfoProdutoCliente{" +  ", quantidadeMesPorFilial=" + Arrays.toString(quantidade) + ", totalGasto=" + Arrays.toString(faturado) + '}';
    }
    
}
