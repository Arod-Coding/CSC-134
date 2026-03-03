import turtle
import colorsys

# --- Setup ---
screen = turtle.Scren()
screen.bgcolor("black")
screen.title("Rainbow Mandala with Initials")

t = turtle.Turtle()
t.speed(0)
t.width(2)
t.hideturtle()

screen.colormode(255)

# --- Spiral Function ---
def draw_spiral():
    """Creates a colorful geometric spiral"""
    iterations = 300

    for i in range (iterations) :
        hue = i / iterations
        rgb = colorsys.hsv_to_rgb(hue, 1, 1)
        color = tuple(int(c * 255) for c in rgb)
        t.color(color)

        t.forward(i * 1.1)
        t.left(13)
        t.right(1)

# --- Initials Function ---
def draw_initials():
    """Draws the initials AR in the center"""
    t.color("white")
    t.width(4)

    # Move to starting position for A
    t.penup()
    t.goto(-40, -20)
    t.pendown()

    # Draw A
    