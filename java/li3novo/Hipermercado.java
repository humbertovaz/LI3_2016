 



import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import static java.util.stream.Collectors.toSet;


public class Hipermercado implements Serializable {
    
    private CatalogoClientes clientes;
    private CatalogoProdutos produtos;
    private Filial filiais[];
    private Faturacao faturacao;
    private String ficheiroLido;
    private int vendaserradas;
    private int totalprodutos;
    private int totalclientes;
    private int totalcompraram;
    private int totalnaocompraram;
    private int comprasnulas;
    private double faturacaoglobal;


    
    public Hipermercado(){
        this.clientes=new CatalogoClientes();
        this.produtos=new CatalogoProdutos();
        for(int i=0;i<3;i++){
            this.filiais[i]= new Filial();
        }
        this.faturacao=new Faturacao();
    }
    

    
    
    public CatalogoClientes getClientes() {
        return clientes;
    }

    public CatalogoProdutos getProdutos() {
        return this.produtos;
    }



    public List<Filial> getFiliais() {
      ArrayList<Filial> tmp = new ArrayList<>();
      for (Filial f : this.filiais){
          tmp.add(f.clone());
      }
      return tmp;
    }
    
    //querie 1
    public List<Produto> produtosNaoVendidos(){
        return this.faturacao.getNaoVendidos();
    }
    
    //querie3
    public TriComprasNProdGastou[] clienteCompras(Cliente c){
        double gastou=0;
        int vendas=0;
        int diferentes=0;
        TriComprasNProdGastou[] res= new TriComprasNProdGastou[12];

        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                gastou+=this.filiais[i].getGastouMes(c,i+1);
                vendas+=this.filiais[i].getVendasClienteMes(c,i+1);
            }
            Set<Produto> set=this.filiais[0].getProdutosCompradosMes(c,i);
            for(int j=1;j<2;j++){
                Set<Produto> aux=this.filiais[j].getProdutosCompradosMes(c,i);
                aux.stream().map(e->set.add(e.clone()));
                aux.clear();
            }
            diferentes=set.size();
            res[i].setVendas(vendas);
            res[i].setDiferentes(diferentes);
            res[i].setGastou(gastou);
            gastou=vendas=diferentes=0;
        }
        return res;
    }
    //querie 2
    public ParNVendasNCliDif vendasRealizadasMes(int mes){
        int vendas=0;
        int clientes=0;
        Set<Cliente> set = this.filiais[0].compraramMes(mes);
        for(int i=1;i<3;i++){
            Set<Cliente> aux = this.filiais[i].compraramMes(mes);
            aux.stream().map(e-> set.add(e.clone()));
            aux.clear();
        }
        clientes=set.size();
        for(int i=0;i<3;i++){
            vendas+=this.filiais[i].getTotalVendasMes(mes);
        }
        return new ParNVendasNCliDif(vendas,clientes);
    }

    // querie 4
    
    public TriComprasNProdGastou[] produtoComprado(Produto p){
        int compras= 0;
        int diferentes=0;
        double totalFaturado=0;
        TriComprasNProdGastou[] res = new TriComprasNProdGastou[12];
        for(int i=0;i<12;i++){
            compras=this.faturacao.getVendasMesProd(p,i+1);
            totalFaturado=this.faturacao.getFaturacaoMesProd(p,i+1);
            Set<Cliente> set = this.filiais[0].getClientesCompraramProdutoMes(p,i+1);
            for(int j=1;j<3;j++){
                Set<Cliente> aux=this.filiais[i].getClientesCompraramProdutoMes(p,i+1);
                aux.stream().map(e->set.add(e.clone()));
                aux.clear();
            }
            diferentes=set.size();
            res[i].setDiferentes(diferentes);
            res[i].setVendas(compras);
            res[i].setGastou(totalFaturado);
            totalFaturado=diferentes=compras=0;
        }
        return res;
    }
    
    //querie 5
    
    
    private int comparaProdQuantidade(ParProdutoQuantidade p1, ParProdutoQuantidade p2){
        if(p1.getQuantidade()<p2.getQuantidade()) return 1;
        if(p1.getQuantidade()>p2.getQuantidade()) return -1;
        else return p1.getProduto().compareTo(p2.getProduto());
    }
    
    
    
    private void concatMapAux(Map<Produto,ParProdutoQuantidade> m, Produto p, ParProdutoQuantidade q){
        if(m.containsKey(p)){
            m.get(p).setQuantidade(m.get(p).getQuantidade()+q.getQuantidade());
        }
        else{
            m.put(p.clone(),q.clone());
        }
    
    }
    
    private void concatMap(Map<Produto,ParProdutoQuantidade> m, Map<Produto,ParProdutoQuantidade> aux){
        aux.forEach((k,v)->concatMapAux(m,k,v));
    }
    
    
    public List<ParProdutoQuantidade> getCompradosCliente(Cliente c){
        Map<Produto,ParProdutoQuantidade> produtos = this.filiais[0].getComprados(c);
        for(int i=1;i<3;i++){
            Map<Produto,ParProdutoQuantidade> aux = this.filiais[i].getComprados(c);
            concatMap(produtos,aux);
        }
        return produtos.entrySet().stream().map(e->e.getValue().clone()).sorted((e1,e2)->comparaProdQuantidade(e1,e2)).collect(Collectors.toList());
    
    }
    // fim querie5
    
    // querie6
    
    public List<ParProdutoQuantidade> getTopXVendidos(int x){
        List<ParProdutoQuantidade> res = this.faturacao.getTopXMaisVendido(x);
        for(int i=0;i<x;i++){
            Set<Cliente> clientes = this.filiais[0].getClientesCompraramProduto(res.get(i).getProduto());
            for(int j=1;j<3;j++){
                Set<Cliente> aux = this.filiais[j].getClientesCompraramProduto(res.get(i).getProduto());
                aux.stream().map(e->clientes.add(e.clone()));
                aux.clear();
            }
            res.get(i).setDiferentes(clientes.size());
        }
        return res;
    }
    
    // +/- a querie7
    
    public List<Cliente> top3Filial(int filial){
        return this.filiais[filial-1].getTop3Buyers();
    }
    
    
    //querie8
    
    private void concatAux(Map<Cliente,Set<Produto>> m, Cliente c, Set<Produto>set){
        if(m.containsKey(c)){
            set.stream().map(e-> m.get(c).add(e.clone()));
        }
        else{
            Set<Produto> res = new HashSet<>();
            set.stream().map(e-> res.add(e.clone()));
            m.put(c,res);
        }
    }
    
    private void concat(Map<Cliente,Set<Produto>> m, Map<Cliente,Set<Produto>> aux){
        aux.forEach((k,v)->concatAux(m,k,v));
    }
    
    private int comparaEntry(Map.Entry<Cliente,Set<Produto>> m1,Map.Entry<Cliente,Set<Produto>> m2 ){
        int size1= m1.getValue().size();
        int size2=m2.getValue().size();
        if(size1<size2) return 1;
        else if(size1>size2) return -1;
        else{
            return m1.getKey().compareTo(m2.getKey());
        }
    }
    
    public List<ParClienteNDif> compraramMaisDiferentes(int x){
        Map<Cliente,Set<Produto>> map = this.filiais[0].getListProd();
        List<ParClienteNDif> res= new ArrayList<>();
        for(int i=1;i<3;i++){
            Map<Cliente,Set<Produto>> aux = this.filiais[i].getListProd();
            concat(map,aux);
        }
        map.entrySet().stream().sorted((e1,e2)-> comparaEntry(e1,e2)).limit(x).forEach(e-> res.add(new ParClienteNDif(e.getKey(),e.getValue().size())));
        return res;
    } 
    // fim querie 8
    
    
    // querie 9
    private int comparaQuantidade(ParClienteQuantidade p1, ParClienteQuantidade p2){
        if(p1.getQuantidade()<p2.getQuantidade()) return 1;
        if(p1.getQuantidade()>p2.getQuantidade()) return -1;
        else return p1.getCliente().compareTo(p2.getCliente());
    }
    
    private void concatAuxBuyers(Map<Cliente,ParClienteQuantidade> m, Cliente c, ParClienteQuantidade p){
        if(m.containsKey(c)){
            m.get(c).setQuantidade(m.get(c).getQuantidade()+p.getQuantidade());
            m.get(c).setGasto(m.get(c).getGasto()+p.getGasto());
        }
        else{
            m.put(c.clone(),p.clone());
        }
    }
    
    private void concatBuyers(Map<Cliente,ParClienteQuantidade> m, Map<Cliente,ParClienteQuantidade> aux){
        aux.forEach((k,v)->concatAuxBuyers(m,k,v));
    }
    
    
    public List<ParClienteQuantidade> getTopXBuyers(Produto p,int x){
        Map<Cliente,ParClienteQuantidade> map = this.filiais[0].compraramProduto(p);
        for(int i=1;i<3;i++){
            Map<Cliente,ParClienteQuantidade> aux = this.filiais[i].compraramProduto(p);
            concatBuyers(map,aux);
        }
        return map.entrySet().stream().sorted((e1,e2)->comparaQuantidade(e1.getValue(),e2.getValue())).limit(x).map(e->e.getValue()).collect(Collectors.toList());
    }
    
    
    // fim querie 9
    public void setClientes(CatalogoClientes clientes) {
        this.clientes = clientes;
    }

    public void setProdutos(CatalogoProdutos produtos) {
        this.produtos = produtos;
    }

   

    

 
    
    
    
}