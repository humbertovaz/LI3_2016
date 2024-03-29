
import java.io.Serializable;


/**
 * Escreva a descrição da classe ParClienteQuantidade aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class ParClienteNDif implements Serializable
{
    // variáveis de instância - substitua o exemplo abaixo pelo seu próprio
    private Cliente cliente;
    private int diferentes;

    /**
     * COnstrutor para objetos da classe ParClienteQuantidade
     */
    public ParClienteNDif()
    {
        this.cliente = new Cliente();
        this.diferentes=0;
    }

    
    public ParClienteNDif(Cliente c, int diferentes)
    {
        this.cliente = c.clone();
        this.diferentes=diferentes;
    }
    
    
    
    public ParClienteNDif(ParClienteNDif p)
    {
        this.cliente = p.getCliente();
        this.diferentes=p.getDiferentes();
    }
    
    
    public Cliente getCliente(){
        return this.cliente.clone();
    }
    
    public int getDiferentes(){
        return this.diferentes;
    }
    
    
    
    public void setDiferentes(int d){
        this.diferentes=d;
    }
    
    
    
    public void setCliente(Cliente c){
        this.cliente=c.clone();
    }
    
    
    public ParClienteNDif clone(){
        return new ParClienteNDif(this);
    }
    
    
    public boolean equals(Object o){
        if (this==o) return true;
        if(this.getClass().equals(o.getClass())){
            ParClienteNDif aux = (ParClienteNDif) o;
            return (aux.getCliente().equals(this.getCliente()) && aux.getDiferentes()==(this.getDiferentes()));
        }
        return false;
    }
    
    
    
}
