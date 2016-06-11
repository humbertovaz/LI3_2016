 



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
        TriComprasNProdGastou[] res=null;

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
            res[i]=new TriComprasNProdGastou(vendas,diferentes,gastou);
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

    
    
    //querie7
    
    public List<Cliente> top3Filial(int filial){
        return this.filiais[filial-1].getTop3Buyers();
    }
    
    public void setClientes(CatalogoClientes clientes) {
        this.clientes = clientes;
    }

    public void setProdutos(CatalogoProdutos produtos) {
        this.produtos = produtos;
    }

   

    

 
    
    
    
}