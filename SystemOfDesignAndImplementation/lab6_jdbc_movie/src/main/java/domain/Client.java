package domain;

public class Client extends BaseEntity<Long> {
    private String cnp;
    private String name;

    public Client(){

    }
    public Client(Long id, String cnp, String name) {
        super.setId(id);
        this.cnp = cnp;
        this.name = name;
    }

    @Override
    public String toString() {
        return "ID: " + super.getId() + " Name: " + name + " CNP: " + cnp;
    }

    public String getCnp() {
        return cnp;
    }

    public void setCnp(String cnp) {
        this.cnp = cnp;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String toXmlString() {
        return "Client{" +
                "id=" + super.getId() +
                ", cnp='" + cnp + '\'' +
                ", name='" + name + '\''
                +'}';
    }
}
