import tkinter as tk
from tkinter import PhotoImage

def on_click(event):
    print(f"Click en coordenadas: ({event.x}, {event.y})")

# Crear ventana principal
ventana = tk.Tk()
ventana.title("Click en Imagen")

# Cargar imagen
# Sustituye "ruta_de_la_imagen.gif" con la ruta de tu imagen en formato .gif
imagen = PhotoImage(file="dificultad_raton.png")  

# Crear un widget Label para mostrar la imagen
label_imagen = tk.Label(ventana, image=imagen)
label_imagen.pack()

# Bindear evento del clic izquierdo
label_imagen.bind("<Button-1>", on_click)

# Iniciar bucle principal
ventana.mainloop()
