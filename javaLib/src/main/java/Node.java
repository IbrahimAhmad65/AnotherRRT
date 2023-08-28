public class Node {
    private final double x;
    private final double y;
    private final double vx;
    private final double vy;
    private final Node parent;
    private final double time;

    public Node(double x, double y, double vx, double vy, Node parent, double time) {
        this.x = x;
        this.y = y;
        this.vx = vx;
        this.vy = vy;
        this.parent = parent;
        this.time = time;
    }

    public Node(Node that){
        this.x = that.x;
        this.y = that.y;
        this.vx = that.vx;
        this.vy = that.vy;
        this.parent = that.parent;
        this.time = that.time;
    }

    public Node getParent() {
        return this.parent;
    }

    public double getTime() {
        return this.time;
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    public double getVX() {
        return this.vx;
    }

    public double getVY() {
        return this.vy;
    }
    public Node setTime(double time){
        return new Node(this.x, this.y, this.vx, this.vy, this.parent, time);
    }

    public Node setParent(Node node){
        return new Node(this.x, this.y, this.vx, this.vy, node, this.time);
    }

    public boolean equals(Node other) {
        return this.x == other.x && this.y == other.y && this.vx == other.vx && this.vy == other.vy;
    }

    public String toString(){
        return "x: " + this.x + " y: " + this.y + " vx: " + this.vx + " vy: " + this.vy;
    }
}
