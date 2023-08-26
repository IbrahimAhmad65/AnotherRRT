import java.util.ArrayList;

import CubicHermite.Cubic;

public class Tree {
    private ArrayList<Node> nodes;

    public Tree() {
        this.nodes = new ArrayList<Node>();
    }

    public Tree(Node start) {
        this.nodes = new ArrayList<Node>();
        this.nodes.add(start);
    }

    public Tree(ArrayList<Node> nodes) {
        this.nodes = (ArrayList<Node>) nodes.clone();
    }

    public Tree AddNode(Node node) {
        Tree newTree = new Tree(this.nodes);
        newTree.nodes.add(node);
        return newTree;
    }

    public ArrayList<Node> getNodes() {
        return this.nodes;
    }

    public String toString() {
        String s = "";

        for (int index = 0; index < nodes.size() - 1; index++) {
            // s += printPathSegment(nodes.get(index), nodes.get(index + 1)) + "\n";
            s += printPathSegmentWithCubicInterp(nodes.get(index), nodes.get(index + 1)) + "\n";
        }
        return s;
    }

    public Tree removeNode(Node node) {
        Tree newTree = new Tree(this.nodes);
        newTree.nodes.remove(node);
        return newTree;
    }

    public static String printPathSegment(Node n1, Node n2) {
        return ("\\operatorname{polygon}\\left(\\left(" + Math.floor(n1.getX() * 1000) / 1000. + ","
                + Math.floor(n1.getY() * 1000) / 1000 + "\\right),\\left(" + Math.floor(n2.getX() * 1000) / 1000 + ","
                + Math.floor(n2.getY() * 1000) / 1000 + "\\right)\\right)");
    }

    public static String printPathSegmentWithCubicInterp(Node n1, Node n2) {

        CubicHermite.Cubic xCubic = CubicHermite.computeCubic(new CubicHermite.Knot(n1.getX(),
                n1.getVX()),
                new CubicHermite.Knot(n2.getX(), n2.getVX()));
        CubicHermite.Cubic yCubic = CubicHermite.computeCubic(new CubicHermite.Knot(n1.getY(),
                n1.getVY()),
                new CubicHermite.Knot(n2.getY(), n2.getVY()));
        String output = "";
        double itr = 10;
        for (int i = 0; i < itr - 1; i++) {
            double t = i / itr;
            double x = xCubic.compute(t);
            double y = yCubic.compute(t);
            double x2 = xCubic.compute(t + 1 / itr);
            double y2 = yCubic.compute(t + 1 / itr);
            output += "\\operatorname{polygon}\\left(\\left(" + Math.floor(x * 1000) / 1000. + ","
                    + Math.floor(y * 1000) / 1000 + "\\right),\\left(" + Math.floor(x2 * 1000) / 1000 + ","
                    + Math.floor(y2 * 1000) / 1000 + "\\right)\\right)\n";

        }
        return output;
    }
}
