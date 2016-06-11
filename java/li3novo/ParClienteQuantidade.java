
import java.io.Serializable;


/**
 * Escreva a descrição da classe ParClienteQuantidade aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class ParClienteQuantidade  implements Serializable
{
    // variáveis de instância - substitua o exemplo abaixo pelo seu próprio
    private Cliente cliente;
    private int quantidade;
    private double gasto;

    /**
     * COnstrutor para objetos da classe ParClienteQuantidade
     */
    public ParClienteQuantidade()
    {
        this.cliente = new Cliente();
        this.quantidade=0;
        this.gasto=0;
    }

    
    public ParClienteQuantidade(Cliente c, int quantidade, double g)
    {
        this.cliente = c.clone();
        this.quantidade=quantidade;
        this.gasto=g;
    }
    
    
    
    public ParClienteQuantidade(ParClienteQuantidade p)
    {
        this.cliente = p.getCliente();
        this.quantidade=p.getQuantidade();
        this.gasto=p.getGasto();
    }
    
    
    public Cliente getCliente(){
        return this.cliente.clone();
    }
    
    public int getQuantidade(){
        return this.quantidade;
    }
    
    
    public double getGasto(){
        return this.gasto;
    }
    
    public void setQuantidade(int q){
        this.quantidade=q;
    }
    
    
    public void setGasto(double g){
        this.gasto=g;
    }
    
    public void setCliente(Cliente c){
        this.cliente=c.clone();
    }
    
    
    public ParClienteQuantidade clone(){
        return new ParClienteQuantidade(this);
    }
    
    
    public boolean equals(Object o){
        if (this==o) return true;
        if(this.getClass().equals(o.getClass())){
            ParClienteQuantidade aux = (ParClienteQuantidade) o;
            return (aux.getCliente().equals(this.getCliente()) && aux.getQuantidade()==(this.getQuantidade()) && aux.getGasto()==this.getGasto());
        }
        return false;
    }
    
    
    
}
