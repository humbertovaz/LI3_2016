
import java.io.Serializable;


/**
 * Escreva a descrição da classe ParProdutoQuantidade aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class ParProdutoQuantidade implements Serializable
{
    // variáveis de instância - substitua o exemplo abaixo pelo seu próprio
    private Produto produto;
    private int quantidade;
    private int diferentes;

    /**
     * COnstrutor para objetos da classe ParprodutoQuantidade
     */
    public ParProdutoQuantidade()
    {
        produto = new Produto();
        quantidade=0;
        diferentes=0;
    }

    
    public ParProdutoQuantidade(Produto p, int quantidade)
    {
        produto = p.clone();
        quantidade=quantidade;
        diferentes=0;
    }
    
    public ParProdutoQuantidade(Produto p, int quantidade, int diferentes)
    {
        produto = p.clone();
        quantidade=quantidade;
        diferentes=diferentes;
    }
    
    public ParProdutoQuantidade(ParProdutoQuantidade p)
    {
        produto = p.getProduto();
        quantidade=p.getQuantidade();
    }
    
    
    public int getDiferentes(){
        return this.diferentes;
    }
    
    public Produto getProduto(){
        return this.produto.clone();
    }
    
    public int getQuantidade(){
        return this.quantidade;
    }
    
    
    
    public void setDiferentes(int d){
        this.diferentes=d;
    }
    
    public void setQuantidade(int d){
        this.quantidade=d;
    }
    
    
    
    public void setProduto(Produto p){
        this.produto=p.clone();
    }
    
    
    public ParProdutoQuantidade clone(){
        return new ParProdutoQuantidade(this);
    }
    
    
    public boolean equals(Object o){
        if (this==o) return true;
        if(this.getClass().equals(o.getClass())){
            ParProdutoQuantidade aux = (ParProdutoQuantidade) o;
            return (aux.getProduto().equals(this.getProduto()) && aux.getQuantidade()==(this.getQuantidade()));
        }
        return false;
    }
}
