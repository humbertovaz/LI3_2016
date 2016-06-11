 



import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;




public class Hipermercado implements Serializable {
    
    private CatalogoClientes clientes;
    private CatalogoProdutos produtos;
    private Filial filiais[];
    private Faturacao faturacao;
    private String ficheiroLido;
    private int vendaserradas;
    private int comprasnulas;
    private double faturacaoglobal;


    
    public Hipermercado(){
        this.clientes=new CatalogoClientes();
        this.produtos=new CatalogoProdutos();
        this.filiais=new Filial[3];
        for(int i=0;i<3;i++){
            this.filiais[i]= new Filial();
        }
        this.faturacao=new Faturacao();
        this.comprasnulas=0;
        this.faturacaoglobal=0;
        this.vendaserradas=0;
        this.comprasnulas=0;
        
    }

    public Hipermercado(CatalogoClientes clientes, CatalogoProdutos produtos, Filial[] filiais, Faturacao faturacao, String ficheiroLido, int vendaserradas, int comprasnulas, double faturacaoglobal) {
        this.clientes = clientes.clone();
        this.produtos = produtos.clone();
        this.filiais = filiais.clone();
        this.faturacao = faturacao.clone();
        this.ficheiroLido = ficheiroLido;
        this.vendaserradas = vendaserradas;
        this.comprasnulas = comprasnulas;
        this.faturacaoglobal = faturacaoglobal;
    }

  
    
    public Hipermercado(Hipermercado f) {
    this.clientes=f.getClientes();
    
    
    
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

   
    
    
    
    
    
    
    
    public void inserCatalogoClientes(String c) {
        this.clientes.insere(c);
    
    }
    
    public void inserCatalogoProdutos(Produto pro) {
    
            this.produtos.insere(pro);
    
    }
    
    public void inserVendas (int filial, String codigoCli , String codigoPro, int quantidade,double faturado,int mes,char modo) {
        
        Produto p = new Produto(codigoPro);
         
        if((mes>=1 && mes<=12) && (filial >=1 && filial <=3 )&& (this.produtos.existe(p)) 
                && this.clientes.existe(codigoCli) && (modo=='N' || modo =='P') && (faturado>=0.0 && faturado<=999.99)
                && quantidade >0) {
                Cliente c = new Cliente (codigoCli);
            this.filiais[filial-1].inserFilial(c, p, quantidade, faturado, mes-1, modo);
            this.faturacao.inser(mes-1, filial-1, faturado, quantidade, p);
            if(faturado==0.0) {
                this.comprasnulas++;
            }
            
        }
        else {this.vendaserradas++;}
    }
    
    
    public void inserProdutoFaturacao (Produto p) {
    
        this.faturacao.inserProduto(p.clone());
    }
    
    
    public void inserClienteFilial(Cliente c) {
        
            for(int i=0;i<3;i++) {
            this.filiais[i].inserClienteFilial(c);
                    }
    }
    
    public int getVendasErradas() {
    return this.vendaserradas;
    }
    
    public int getTamanho() {
    
    return this.clientes.getTotalClientes();
    }
    
    public CatalogoClientes  getCatalogo() {
    return this.clientes.clone();
    }
    
    public int getTamanhoFilial() {
    
        int soma=0;
        
        for(int i=0;i<3;i++) {
        
            soma += this.filiais[i].getInformacaoClientes().size();
        
        }
    return soma;
    }
 
    
    
    
}