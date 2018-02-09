from kivy.uix.dropdown import DropDown
from kivy.uix.button import Button
from kivy.base import runTouchApp

# create a dropdown with 10 buttons
dropdown = DropDown()
'''
for index in range(10):
    # When adding widgets, we need to specify the height manually
    # (disabling the size_hint_y) so the dropdown can calculate
    # the area it needs.

    btn = Button(text='Value %d' % index, size_hint_y=None, height=44)

    # for each button, attach a callback that will call the select() method
    # on the dropdown. We'll pass the text of the button as the data of the
    # selection.
    btn.bind(on_release=lambda btn: dropdown.select(btn.text))

    # then add the button inside the dropdown
    dropdown.add_widget(btn)
'''
b1=Button(text='water', size_hint_y=None, height=50)
b1.bind(on_release=lambda b1: dropdown.select(b1.text))
dropdown.add_widget(b1)

b2=Button(text='sugar', size_hint_y=None, height=50)
b2.bind(on_release=lambda b2: dropdown.select(b2.text))
dropdown.add_widget(b2)

b3=Button(text='sleep', size_hint_y=None, height=50)
b3.bind(on_release=lambda b3: dropdown.select(b3.text))
dropdown.add_widget(b3)

b4=Button(text='Blood pressure', size_hint_y=None, height=50)
b4.bind(on_release=lambda b4: dropdown.select(b4.text))
dropdown.add_widget(b4)

b5=Button(text='Calories', size_hint_y=None, height=50)
b5.bind(on_release=lambda b5: dropdown.select(b5.text))
dropdown.add_widget(b5)

# create a big main button
mainbutton = Button(text='Daily Analysis', size_hint=(None, None))

# show the dropdown menu when the main button is released
# note: all the bind() calls pass the instance of the caller (here, the
# mainbutton instance) as the first argument of the callback (here,
# dropdown.open.).
mainbutton.bind(on_release=dropdown.open)

# one last thing, listen for the selection in the dropdown list and
# assign the data to the button text.
dropdown.bind(on_select=lambda instance, x: setattr(mainbutton, 'text', x))

runTouchApp(mainbutton)

