 
import java.util.*;
import java.util.stream.Collectors.*;
import java.util.stream.*;


public class Faturacao {
    private int totalVendas;
    private double totalFaturado;
    private HashMap<Produto, InfoProduto> produtosVendidos;
    
    public Faturacao(){
        this.totalVendas=0;
        this.totalFaturado=0;
        this.produtosVendidos=new HashMap<>();
    
    }
    public Faturacao(Faturacao faturacao){
        this.totalVendas=faturacao.getTotalVendas();
        this.totalFaturado=faturacao.getTotalFaturado();
        this.produtosVendidos=(HashMap<Produto, InfoProduto>) faturacao.getProdutosVendidos();
    }
    public Faturacao(int totalVendas, double totalFaturado, HashMap<Produto,InfoProduto> produtosVendidos) {
        this.totalVendas = totalVendas;
        this.totalFaturado = totalFaturado;
        this.produtosVendidos=new HashMap<>();
        produtosVendidos.forEach((k,v)->this.produtosVendidos.put(k,v));
    }
    
    
    public int getTotalVendas() {
        return totalVendas;
    }

    public double getTotalFaturado() {
        return totalFaturado;
    }

    
    private int add(int t, int v){
        t+=v;
        return t;
    }
    
    
    public int getVendasMesProd(Produto p,int mes){
        int res=0;
        if(this.produtosVendidos.containsKey(p)){
            res=this.produtosVendidos.get(p).getVendasMes(mes);
        }
        return res;
    }
    
    
    public double getFaturacaoMesProd(Produto p,int mes){
        double res=0;
        if(this.produtosVendidos.containsKey(p)){
            res=this.produtosVendidos.get(p).getFaturadoMes(mes);
        }
        return res;
    }
    
    
    public int getTotalVendasMes(int mes){
        return this.produtosVendidos.values().stream().mapToInt(i-> i.getVendasMes(mes)).sum();
    }
    
    public Map<Produto,InfoProduto> getProdutosVendidos() {
        TreeMap<Produto,InfoProduto> tmp = new TreeMap<>();
        for(Map.Entry<Produto, InfoProduto> entry : produtosVendidos.entrySet()){
            tmp.put(entry.getKey().clone(), entry.getValue().clone());
        }
        return tmp;
    }
    public void setTotalVendas(int totalVendas) {
        this.totalVendas = totalVendas;
    }

    public void setTotalFaturado(double totalFaturado) {
        this.totalFaturado = totalFaturado;
    }

    public void setProdutosVendidos(TreeMap<Produto,InfoProduto> produtosVendidos) {
        this.produtosVendidos.clear();
        produtosVendidos.forEach((k,v)-> this.produtosVendidos.put(k,v));
    }
    
    private void listAdd(List<Produto> l, Produto p, InfoProduto i){
        if (!(i.comprado())){
            l.add(p.clone());
        }
    }
    
    private int produtoQuantidadeComp(ParProdutoQuantidade p1,ParProdutoQuantidade p2){
        if(p1.getQuantidade()<p2.getQuantidade()) return 1;
        else if(p1.getQuantidade()>p2.getQuantidade()) return -1;
        else return p1.getProduto().compareTo(p2.getProduto());
    }
    
    public List<ParProdutoQuantidade> getTopXMaisVendido(int x){
        List<ParProdutoQuantidade> res = new ArrayList<>();
        this.produtosVendidos.forEach((k,v)->res.add(new ParProdutoQuantidade(k.clone(),v.getQuantidadeTotal())));
        return res.stream().sorted((e1,e2)->produtoQuantidadeComp(e1,e2)).limit(x).collect(Collectors.toList());
    }
    
    public List<Produto> getNaoVendidos(){
        List<Produto> res = new ArrayList<>();
        this.produtosVendidos.forEach((k,v)->listAdd(res,k,v));
        return res.stream().sorted((e1,e2)->e1.getCodigoProduto().compareTo(e2.getCodigoProduto())).collect(Collectors.toList());
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
        final Faturacao other = (Faturacao) obj;
        if (this.totalVendas != other.totalVendas) {
            return false;
        }
        if (Double.doubleToLongBits(this.totalFaturado) != Double.doubleToLongBits(other.totalFaturado)) {
            return false;
        }
        if (!Objects.equals(this.produtosVendidos, other.produtosVendidos)) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Faturacao{" + "totalVendas=" + totalVendas + ", totalFaturado=" + totalFaturado + ", produtosVendidos=" + produtosVendidos + '}';
    }
    
    @Override
    public Faturacao clone() {
        return new Faturacao(this);
    }
    
    
    
}
