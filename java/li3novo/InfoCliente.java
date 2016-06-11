 
import java.util.*;
import java.util.Map.Entry;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * 
 */
class InfoCliente {
   private double[] dinheiroGastoMes;
   private double[] totalCompradoMes;
   private int [] vendas;
   private int totalComprado;
   private double totalGasto;
   private Map <Produto,InfoProdutoCliente> produtosComprados[]; // modos N P
    
   public InfoCliente(){
       this.dinheiroGastoMes= new double[12];
       this.totalCompradoMes= new double [12];
       this.totalComprado=0;
       for(int i=0;i<12;i++){
           this.vendas[i]=0;
       }
       for(int i=0;i<2;i++){
           this.produtosComprados[i] = new TreeMap<>();
       }
   }

    public InfoCliente(double[] dinheiroGastoMes, double[] totalCompradoMes, int totalComprado, Map<Cliente, InfoProdutoCliente> produtosComprados[],int []vendas) {
        this.dinheiroGastoMes = dinheiroGastoMes;
        this.totalCompradoMes = totalCompradoMes;
        this.totalComprado = totalComprado;

        for(int i=0;i<12;i++){
            this.vendas[i]=0;
        }
        for(int i=0;i<2;i++){
            this.produtosComprados[i].clear(); 
            for (Map.Entry<Produto,InfoProdutoCliente> entry: this.produtosComprados[i].entrySet()){
                this.produtosComprados[i].put(entry.getKey(),entry.getValue());
            }
        }
    }
    public InfoCliente(InfoCliente ic){
        this.dinheiroGastoMes=ic.getDinheiroGastoMes();
        this.totalCompradoMes = ic.getTotalCompradoMes();
        this.totalComprado = ic.getTotalComprado();
        for(int i=0;i<12;i++){
            this.vendas[i]=ic.getVendasMes(i);
        }
        this.produtosComprados[0] = ic.getProdutosComprados('N');
        this.produtosComprados[1] = ic.getProdutosComprados('P');
    }
   
   public int getVendasMes(int i){
       return this.vendas[i];
   }
   
   public double getTotalGasto(){
       return this.totalGasto;
   }
   
   public double getGastouMes(int i){
       return this.dinheiroGastoMes[i];
   }
   
   public void setVendasMes(int i, int v){
       this.vendas[i]=v;
   }
   
   public double[] getDinheiroGastoMes() {
        return dinheiroGastoMes;
   }

   public double[] getTotalCompradoMes() {
        return totalCompradoMes;
   }

   public int getTotalComprado() {
        return totalComprado;
   }
   
   private void produtosCompradosMesAux(Set<Produto> set, Produto p,InfoProdutoCliente i, int mes){
       if(i.compradoMes(mes)){
           set.add(p.clone());
       }
   }
   
   public Set<Produto> produtosCompradosMes(int mes){
       Set<Produto> res= new HashSet<>();
       this.produtosComprados[0].forEach((k,v)->produtosCompradosMesAux(res,k,v,mes));
       this.produtosComprados[1].forEach((k,v)->produtosCompradosMesAux(res,k,v,mes));
       return res;
   }
   
   
   public int getComprasProdutoMes(Produto p, int mes){
       int res=0;
       if(this.produtosComprados[0].containsKey(p)){
           res+=this.produtosComprados[0].get(p).getComprasMes(mes);
       }
       if(this.produtosComprados[1].containsKey(p)){
           res+=this.produtosComprados[1].get(p).getComprasMes(mes);
       }
       return res;
   }
   
   
   
   public double getFaturadoProdutoMes(Produto p, int mes){
       double res=0;
       if(this.produtosComprados[0].containsKey(p)){
           res+=this.produtosComprados[0].get(p).getFaturadoMes(mes);
       }
       if(this.produtosComprados[1].containsKey(p)){
           res+=this.produtosComprados[1].get(p).getFaturadoMes(mes);
       }
       return res;
   }
   
   
   public Map<Produto, InfoProdutoCliente> getProdutosComprados(char m) {
       TreeMap<Produto,InfoProdutoCliente> tmp= new TreeMap<>();
       int modo=0;
       if(m=='P') modo=1;
       for (Map.Entry<Produto, InfoProdutoCliente> e: this.produtosComprados[modo].entrySet()){
            tmp.put(e.getKey(),e.getValue());
       }
       return tmp;
   }

   public void setDinheiroGastoMes(double[] dinheiroGastoMes) {
       this.dinheiroGastoMes = dinheiroGastoMes;
   }

   public void setTotalComoradoMes(double[] totalComoradoMes) {
       this.totalCompradoMes = totalComoradoMes;
   }

   public void setTotalComprado(int totalComprado) {
       this.totalComprado = totalComprado;
   }
    
   
   public boolean comprouMes(int mes){
       if(this.totalCompradoMes[mes-1]>0) return true;
       else return false;
   }
   
   public boolean comprou(Produto p){
       boolean found= false;
       for(int i=0; i<2 && !found; i++){
           if(this.produtosComprados[i].containsKey(p)){
               found=true;
           }
       }
       return found;
   }
   
   
   public int getQuantidadeProduto(Produto p){
       int res=0;
       for(int i=0;i<2;i++){
           if(produtosComprados[i].containsKey(p)){
               InfoProdutoCliente aux = produtosComprados[i].get(p).clone();
               res+=aux.getQuantidadeTotal();
           }
       }
       return res;
   }
   
   public double getGastouProduto(Produto p){
       int res=0;
       for(int i=0;i<2;i++){
           if(produtosComprados[i].containsKey(p)){
               InfoProdutoCliente aux = produtosComprados[i].get(p).clone();
               res+=aux.getTotalFaturado();
           }
       }
       return res;
   }
   
   
   public boolean produtoCompradoMes(Produto p, int mes){
       if(this.produtosComprados[0].containsKey(p)){
           return this.produtosComprados[0].get(p).compradoMes(mes);
       }       
       
       if(this.produtosComprados[1].containsKey(p)){
           return this.produtosComprados[1].get(p).compradoMes(mes);
       }
       else return false;
   }
   
   public Set<Produto> getProds(){
       Set<Produto> res = new HashSet<>();
       this.produtosComprados[0].forEach((k,v)->res.add(k.clone()));
       this.produtosComprados[1].forEach((k,v)->res.add(k.clone()));
       return res;
   }
   
   public void setProdutosComprados(Map<Produto, InfoProdutoCliente> produtosComprados, int m) {
       int modo=0;
       if(m=='P') modo=1;
       this.produtosComprados[modo].clear();
       for(Map.Entry<Produto, InfoProdutoCliente> entry : produtosComprados.entrySet()){
           this.produtosComprados[modo].put(entry.getKey(), entry.getValue());
       }
   }
   public InfoCliente clone(){
       return new InfoCliente(this);
   }
}
