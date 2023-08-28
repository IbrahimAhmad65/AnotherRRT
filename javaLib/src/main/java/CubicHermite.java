import java.util.function.Function;

public final class CubicHermite {
    public static Cubic computeCubic(Knot initial, Knot end) {
        double a = 2 * initial.getX() - 2 * end.getX() + initial.getVX() + end.getVX();
        double b = -3 * initial.getX() + 3 * end.getX() - 2 * initial.getVX() - end.getVX();
        double c = initial.getVX();
        double d = initial.getX();
        return new Cubic(a, b, c, d);
    }

    public static Cubic[] computeCubeCubics(XYKnot initial, XYKnot end) {
        Cubic xCubic = computeCubic(initial.getX(), end.getX());
        Cubic yCubic = computeCubic(initial.getY(), end.getY());
        return new Cubic[] { xCubic, yCubic };
    }

    public static double getSecondsToTraverse(Cubic xCubic, Cubic yCubic, double maxAccel) {
//        Function<Double, Double> accelMagnitudeFunction = (x) -> Math.sqrt(
//                x * x * 36 * (xCubic.a * xCubic.a + yCubic.a * yCubic.a)
//                        + x * 24 * (xCubic.a * xCubic.b + yCubic.a * yCubic.b)
//                        + 4 * (xCubic.b * xCubic.b + yCubic.b * yCubic.b));
        double testBound1 = accelMagnitudeFunction(0.0,xCubic,yCubic);
        double testBound2 = accelMagnitudeFunction(1.0,xCubic,yCubic);
        double a = xCubic.a;
        double b = xCubic.b;
        double a1 = yCubic.a;
        double b1 = yCubic.b;
        // Not actually the right number, but has the same x value for all values of a,b
        // a1,b1
        double derivativeOfAccelZero = (-a * b - a1 * b1) / (3 * (a * a + a1 * a1));
        double testMaybe = accelMagnitudeFunction(derivativeOfAccelZero,xCubic,yCubic);
        double maxAccelcurrent = Math.max(testBound1, Math.max(testBound2, testMaybe));

        return maxAccelcurrent / maxAccel;
    }

    public static double accelMagnitudeFunction(double x, Cubic xCubic, Cubic yCubic) {
        return Math.sqrt(
                x * x * 36 * (xCubic.a * xCubic.a + yCubic.a * yCubic.a)
                        + x * 24 * (xCubic.a * xCubic.b + yCubic.a * yCubic.b)
                        + 4 * (xCubic.b * xCubic.b + yCubic.b * yCubic.b));
    }

    public static void main(String[] args) {
        Cubic xCubic = new Cubic(7.1, -7.9, 1, 2);
        Cubic yCubic = new Cubic(.4, .4, 1, 1.2);
    }

    public static class XYKnot {
        private final Knot x;
        private final Knot y;

        public XYKnot(Knot x, Knot y) {
            this.x = x;
            this.y = y;
        }

        public Knot getX() {
            return this.x;
        }

        public Knot getY() {
            return this.y;
        }

    }

    public static class Knot {
        private final double x;
        private final double vx;

        public Knot(double x, double vx) {
            this.x = x;
            this.vx = vx;
        }

        public double getX() {
            return this.x;
        }

        public double getVX() {
            return this.vx;
        }
    }

    public static class Cubic {
        private final double a;
        private final double b;
        private final double c;
        private final double d;

        public Cubic(double a, double b, double c, double d) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
        }

        public double compute(double t) {
            return (((this.a * t) + this.b) * t + this.c) * t + this.d;
        }

        public double getMaximum() {
            return -this.b / (3 * this.a);
        }
    }
}
