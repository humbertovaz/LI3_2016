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
public class InfoProduto {
    private int [][] quantidade; // [12][3] mes, filial
    private int quantidadeTotal;
    private double [][] faturado; // [12][3] mes, filial
    private double totalFaturado;
    private int[][] vendas;

    
    public InfoProduto(){
        this.quantidadeTotal=0;
        this.totalFaturado=0;
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                faturado[i][j]=0;
                quantidade[i][j]=0;
                vendas[i][j]=0;
            }
        }
    }
    public InfoProduto(int[][] quantidade, double[][] faturado, double totalFaturado,int quantidadeTotal, int [][]vendas) {
        this.quantidadeTotal = quantidadeTotal;
        this.totalFaturado = totalFaturado;
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                this.quantidade[i][j]=quantidade[i][j];
                this.faturado[i][j]=faturado[i][j];
                this.vendas[i][j]=vendas[i][j];
            }
        }
    }
    public InfoProduto (InfoProduto o){
        this.quantidadeTotal=o.getQuantidadeTotal();
        this.totalFaturado=o.getTotalFaturado();
        this.faturado=o.getFaturado();
        this.quantidade=o.getQuantidade();
        this.vendas=o.getVendas();
    }

    public int[][] getVendas(){
        int[][] res= new int[12][3];
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                res[i][j]=this.vendas[i][j];
            }
        }
        return res;
    }

    public int getQuantidadeTotal() {
        return this.quantidadeTotal;
    }

    public double getTotalFaturado() {
        return totalFaturado;
    }

    public double[][] getFaturado(){
        double fat[][]=new double[12][3];
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                fat[i][j]=this.faturado[i][j];
            }
        }
        return fat;
    }
    
    
    public double getFaturadoMes(int mes){
        double res=0;
        for(int i=0;i<3;i++){
            res+=this.faturado[mes-1][i];
        }
        return res;
    }
    
    public int getVendasMes(int mes){
        int total=0;
        for(int i=0;i<3;i++){
            total+=this.vendas[mes-1][i];
        }
        return total;
    }
    
    public int[][] getQuantidade(){
        int quant[][]=new int[12][3];
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                quant[i][j]=this.quantidade[i][j];
            }
        }
        return quant;
    }
    
    public void setVendas(int [][]v){
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                this.vendas[i][j]=v[i][j];
            }
        }
    }

    public void setQuantidadeMesPorFilial(int[][] quantidade) {
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                this.quantidade[i][j]=quantidade[i][j];
            }
        }
    }

    public void setTotalGasto(double[][] faturado) {
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                this.faturado[i][j]=faturado[i][j];
            }
        }
    }
    
    public boolean comprado(){
        return (this.quantidadeTotal>0);
    }
    
    public InfoProduto clone(){
        return new InfoProduto(this);
    }

    @Override
    public String toString() {
        return "InfoProduto{" +  ", quantidadeMesPorFilial=" + Arrays.toString(quantidade) + ", totalGasto=" + Arrays.toString(faturado) + '}';
    }
    
}
