import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Button, Slider
from tkinter import filedialog
from tkinter import Tk

class InteractiveCurve:
    def __init__(self):
        # Initial data points
        self.xs = np.linspace(0, 1, 10)
        self.ys = np.exp(self.xs)
        self.ys = np.interp(self.ys, (self.ys.min(), self.ys.max()), (0, 1))  # Normalize
        
        # Create a figure and axis
        self.fig, self.ax = plt.subplots()
        plt.subplots_adjust(bottom=0.2)
        
        # Line plot
        self.line, = self.ax.plot(self.xs, self.ys, 'o-', picker=5)  # 5 points tolerance for picking

        # Add button for adding points
        self.add_point_ax = plt.axes([0.7, 0.05, 0.1, 0.075])
        self.add_point_button = Button(self.add_point_ax, 'Add Point')
        self.add_point_button.on_clicked(self.add_point)

        # Add button for saving the curve
        self.save_curve_ax = plt.axes([0.8, 0.05, 0.1, 0.075])
        self.save_curve_button = Button(self.save_curve_ax, 'Save Curve')
        self.save_curve_button.on_clicked(self.save_curve)

        # Connect the canvas event
        self.fig.canvas.mpl_connect('pick_event', self.on_pick)
        self.fig.canvas.mpl_connect('button_release_event', self.on_release)
        self.fig.canvas.mpl_connect('motion_notify_event', self.on_motion)
        
        self.dragging_point = None

    def add_point(self, event):
        new_x = np.mean(self.xs)
        new_y = np.mean(self.ys)
        self.xs = np.append(self.xs, new_x)
        self.ys = np.append(self.ys, new_y)
        self.xs, self.ys = zip(*sorted(zip(self.xs, self.ys)))
        self.xs, self.ys = np.array(self.xs), np.array(self.ys)
        self.update_plot()

    def on_pick(self, event):
        if event.artist == self.line:
            mouse_event = event.mouseevent
            self.dragging_point = event.ind

    def on_motion(self, event):
        if self.dragging_point is not None:
            x, y = event.xdata, event.ydata
            if x is not None and y is not None:
                self.xs[self.dragging_point] = x
                self.ys[self.dragging_point] = y
                self.update_plot()

    def on_release(self, event):
        if self.dragging_point is not None:
            self.dragging_point = None

    def update_plot(self):
        # Update data
        self.line.set_data(self.xs, self.ys)
        self.ax.relim()
        self.ax.autoscale_view()
        self.fig.canvas.draw()

    def save_curve(self, event):
        root = Tk()
        root.withdraw()
        filename = filedialog.asksaveasfilename(defaultextension=".txt")
        root.destroy()
        if filename:
            with open(filename, 'w') as f:
                for x, y in zip(self.xs, self.ys):
                    f.write(f"{x} {y}\n")
            print("Curve saved to", filename)

if __name__ == '__main__':
    curve = InteractiveCurve()
    plt.show()
