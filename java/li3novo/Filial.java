 
import java.util.*;
import java.util.stream.Collectors;
/**
 *
 *
 */
public class Filial {
    private Map<Cliente,InfoCliente> informacaoClientes; // // está correto



    public Filial( Map<Cliente, InfoCliente> informacaoClientes) {
        this.informacaoClientes= new HashMap<>();
        for (Map.Entry<Cliente, InfoCliente> entry : informacaoClientes.entrySet()){
            this.informacaoClientes.put(entry.getKey().clone(), (InfoCliente) entry.getValue().clone());
        }     
    }
    public Filial() {
        this.informacaoClientes=new TreeMap<>();
    }
    public Filial (Filial f){
        this.informacaoClientes=f.getInformacaoClientes();
    }
    public Map<Cliente,InfoCliente> getInformacaoClientes (){
        TreeMap<Cliente,InfoCliente> tmp= new TreeMap<>();
        this.informacaoClientes.forEach((k,v)->tmp.put(k.clone(),v.clone()));
        return tmp;
    }
    
    
    private void addListP(List<Cliente> l, Cliente c, InfoCliente i, Produto p){
        if(i.comprou(p)){
            l.add(c);
        }
    }
    
    private int compareDouble(double d,double d2){
        Double obj1 = new Double(d);
        Double obj2 = new Double(d2);
        return obj2.compareTo(obj1);
    }
    
    public List<Cliente> getTop3Buyers(){
        List<Cliente> res=new ArrayList<>();
        informacaoClientes.entrySet().stream()
        .sorted((e1,e2)->compareDouble(e1.getValue().getTotalGasto(),e2.getValue().getTotalGasto())) 
        .limit(3) 
        .forEach(e->res.add(e.getKey().clone()));
        return res;
    }
    
    public double getGastouMes(Cliente c, int mes)
    {
        if (this.informacaoClientes.containsKey(c)){
            InfoCliente aux=this.informacaoClientes.get(c).clone();
            return aux.getGastouMes(mes);
            
        }
        else return 0;
    }
    
    private void addListM(List<Cliente> l, Cliente c, InfoCliente i){
        int total=0;
        for(int j=0;j<12;j++){
            total+=i.getVendasMes(j);
        }
        if(total>0) l.add(c);
    }
    public List<Cliente> comprouMes(int i){
        List<Cliente> res = new ArrayList<>();
        this.informacaoClientes.forEach((k,v)->addListM(res,k,v));
        return res;
    }
    
    
    public Set<Cliente> compraramMes(int mes){
        Set<Cliente> res = new HashSet<>();
        this.informacaoClientes.entrySet().stream().filter(e -> e.getValue().comprouMes(mes-1)).map(e -> res.add(e.getKey().clone()));
        return res;
    }
    
    
    
    public Set<Cliente> getClientesCompraramProdutoMes(Produto p, int mes){
        Set<Cliente> res = new HashSet<>();
        this.informacaoClientes.entrySet().stream().filter(e -> e.getValue().produtoCompradoMes(p,mes)).map(e-> res.add(e.getKey().clone()));
        return res;
    }
    
    public Set<Cliente> getClientesCompraramProduto(Produto p){
        Set<Cliente> res = this.getClientesCompraramProdutoMes(p,1);
        for(int i=2;i<13;i++){
            Set<Cliente> aux = this.getClientesCompraramProdutoMes(p,i);
            aux.stream().map(e->res.add(e.clone()));
        }
        return res;
    
    }
    
    public double faturadoProdutoMes(Produto p, int mes){
        double res=0;
        for(InfoCliente i: this.informacaoClientes.values()){
            res+=i.getFaturadoProdutoMes(p,mes);
        }
        return res;
    }
    
    private void addCliQuant(Map<Cliente,ParClienteQuantidade> m, InfoCliente i, Cliente c, Produto p){
        if(i.comprou(p)){
            if(m.containsKey(c)){
                ParClienteQuantidade aux = m.get(c);
                aux.setQuantidade(aux.getQuantidade()+i.getQuantidadeProduto(p));
                aux.setGasto(aux.getGasto()+i.getGastouProduto(p));
            }
            else{
                ParClienteQuantidade aux = new ParClienteQuantidade(c,i.getQuantidadeProduto(p),i.getGastouProduto(p));
                m.put(c.clone(),aux);
            }
        }
    }
    
    public Map<Cliente,ParClienteQuantidade> compraramProduto(Produto p){
        Map<Cliente,ParClienteQuantidade> res= new HashMap<>();
        this.informacaoClientes.forEach((k,v)-> addCliQuant(res,v,k,p));
        return res;
    }
    
    public Set<Produto> getProdutosCompradosMes(Cliente c, int mes){
        Set<Produto> res = new HashSet<>();
        if(this.informacaoClientes.containsKey(c)){
            res=this.informacaoClientes.get(c).produtosCompradosMes(mes);
        }
        return res;
    }
    
    
    public int getQuantidadeComprada(Cliente c, Produto p){
        if(this.informacaoClientes.containsKey(c)){
            return this.informacaoClientes.get(c).getQuantidadeProduto(p);
        }
        return 0;
    }
    
    public Map<Produto,ParProdutoQuantidade> getComprados(Cliente c){
        Set<Produto> produtos = getProdutosCompradosMes(c,1);
        Map<Produto,ParProdutoQuantidade> res = new HashMap<>();
        for(int i=2;i<13;i++){
            Set<Produto> aux = getProdutosCompradosMes(c,i);
            aux.stream().map(e->produtos.add(e.clone()));
            aux.clear();
        }
        produtos.stream().map(e->res.put(e.clone(),new ParProdutoQuantidade(e.clone(),this.getQuantidadeComprada(c,e))));
        return res;
    }
    
    public int getVendasClienteMes(Cliente c, int mes){
        if(this.informacaoClientes.containsKey(c)){
            return this.informacaoClientes.get(c).getVendasMes(mes);
        }
        return 0;
    }
    
    public int getTotalVendasMes(int mes){
        int res=0;
        for(InfoCliente i: this.informacaoClientes.values()){
            res+=i.getVendasMes(mes-1);
        }
        return res;
    }
    
    public Map<Cliente, Set<Produto>> getListProd(){
        Map<Cliente,Set<Produto>> res = new HashMap<>();
        this.informacaoClientes.forEach((k,v)->res.put(k,v.getProds()));
        return res;
    }



    public Filial clone(){
        return new Filial(this);
    }
    
}
