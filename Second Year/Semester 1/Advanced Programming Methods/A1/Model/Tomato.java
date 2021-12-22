package Model;

public class Tomato implements IVegetable {
    private float weight;

    public Tomato(float weight) {
        this.weight = weight;
    }

    @Override
    public float getWeight() {
        return this.weight;
    }

    @Override
    public void setWeight(float weight) {
        this.weight = weight;
    }

    @Override
    public String toText() {
        return "Tomato with the weight: " + this.weight + " kg.";
    }
}
