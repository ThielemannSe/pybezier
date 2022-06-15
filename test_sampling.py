import unittest
from pybezier import Bezier, Vec2

class TestBezier(unittest.TestCase):

    curve_1 = Bezier([
        (100, 200),
        (300, 400),
        (400, 100)
    ])

    def test_endpoint(self):
        self.assertEqual(Vec2(400, 100).x, self.curve_1.endpoint().x)
        self.assertEqual(Vec2(400, 100).y, self.curve_1.endpoint().y)

    def test_startpoint(self):
        self.assertEqual(Vec2(100, 200).x, self.curve_1.startpoint().x)
        self.assertEqual(Vec2(100, 200).y, self.curve_1.startpoint().y)

    def test_sample(self):

        for i in [12, 20, 100, 200]:
            step_width = i
            points = self.curve_1.sample_equidistant(step_width, 0.001, 0)
            length = self.curve_1.length()
            
            # number of sampled points must be less or equal than the length of the curve
            # devided by the step width 
            self.assertLessEqual(len(points), length/step_width, "Number of sampled points is to large")

            # If step_width is less than length of the curve, at least one point must be returned
            if step_width < length:
                self.assertGreaterEqual(len(points), 1)

            # The distance between the last sampled point and the endpoint of the curve must
            # be smaller than step_width
            last = points[-1]
            endpoint = self.curve_1.endpoint()
            distance = last.distance(endpoint)
            print(distance)
            self.assertLessEqual(distance, step_width)




if __name__ == "__main__":
    unittest.main()