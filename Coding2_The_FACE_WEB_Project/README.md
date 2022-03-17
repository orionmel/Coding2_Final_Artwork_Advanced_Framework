THE FACE WEB
============
Project Summary
----------
Bonus :
I am very interested in what I learned in term 2 of Creative Coding Class , such as opencv and numpy, and I am eager to try to make a website myself, so I made an additional website which name is “THE FACE WEB"

Github link： 
--------
https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework

Video link： 
--------
https://vimeo.com/689315352

More detail link： 
--------
https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework/blob/main/Coding2_The_FACE_WEB_Project/THE_FACE_WEB.pdf

----------------------
## INTRODUCTION
![](https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework/blob/main/Coding2_The_FACE_WEB_Project/website.png)
**Welcome to the website of THE FACE WEB, which was created using tools such as opencv, python, PyTorch, streamlit, numpy, and more.**

**On this Website, there are three different modes.**

**In Image Recognition mode: This is a picture recognition system.You can upload your own images to see the number of faces in the uploaded images**

**In Video Recognition Mode: This is a video recognition system where you can upload videos, and the website will recognize the number of faces of people in the video**

**In Style Transfer mode: You can select different pictures about "faces" provided by the system, and then select different styles to convert the pictures**


## Process
### 1.Input the basic python tools
``` 
import streamlit as st
import mediapipe as mp
import cv2
import numpy as np
import tempfile
import time
from PIL import Image
import style
import saved_models
```

### 2.Familiar with streamlit code
``` 
st.title(' ***THE FACE WEB*** ')
st.markdown (
    """
    <style>
    [data-testid = "stSidebar"][aria-expanded = "true"] > div:first-child{
        width:350px
    }
    [data-testid = "stSidebar"][aria-expanded = "false"] > div:first-child{
        width:350px
        margin-left : -350px
    }
    </style>
    """,
    unsafe_allow_html=True,
)

#sidebar title
st.sidebar.title("***THE FACE*** Sidebar")
st.sidebar.subheader('Mode selection')

#select bar
app_mode = st.sidebar.selectbox('Choose the App mode',
                                ['Introduction','Image Recognition','Video Recognition','Style Transfer']
                                )

``` 

### 3.facemesh in the image
``` 
with mp_face_mesh.FaceMesh(
    static_image_mode= True,
    max_num_faces=max_faces,
    min_detection_confidence= detection_confidence) as face_mesh:
        results = face_mesh.process(image)
        out_image = image.copy()

        #Face landmark drawing
        for face_landmarks in results.multi_face_landmarks:
            face_count +=1

            mp_drawing.draw_landmarks(
            image = out_image,
            landmark_list= face_landmarks,
            connections = mp_face_mesh.FACEMESH_CONTOURS,
            landmark_drawing_spec = drawing_spec)

           # write the number of face
            kpil_text.write(f"<h1 style='text-align:center;color:red;'>{face_count}</h1>",unsafe_allow_html=True)

        #show image
        st.subheader('Output Image')
        st.image(out_image,use_column_width=True)
``` 
![](https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework/blob/main/Coding2_The_FACE_WEB_Project/facemesh.png)

### 4.facemesh in the video
``` 
with mp_face_mesh.FaceMesh(
    max_num_faces=max_faces,
    min_detection_confidence=detection_confidence,
    min_tracking_confidence=tracking_confidence
    ) as face_mesh:
        prevTime = 0

        while vid.isOpened():
            i += 1
            ret,frame = vid.read()
            if not ret:
                continue


            results = face_mesh.process(frame)
            frame.flags.writeable = True


            face_count = 0
            if results.multi_face_landmarks:
                for face_landmarks in results.multi_face_landmarks:
                    face_count += 1

                    mp_drawing.draw_landmarks(
                        image= frame,
                        landmark_list=face_landmarks,
                        connections=mp_face_mesh.FACEMESH_CONTOURS,
                        landmark_drawing_spec=drawing_spec,
                        connection_drawing_spec=drawing_spec)

            currTime = time.time()
            fps = 1/(currTime - prevTime)
            prevTime = currTime

            if record:
                out.write(frame)

``` 
![](https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework/blob/main/Coding2_The_FACE_WEB_Project/facemesh2.png)

### 5.Style transfer
I mainly used the pytroch tool, and at the same time used several model paths that have been trained for style conversion, which can be seen [style.py](https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework/blob/main/Coding2_The_FACE_WEB_Project/face_web/style.py) files.

## Tips
I mainly used the pytroch tool, and at the same time used several model paths that have been trained for style conversion, which can be seen [style.py](https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework/blob/main/Coding2_The_FACE_WEB_Project/face_web/style.py) files.

If you want to know more code information, check out the links below :
https://github.com/orionmel/Coding2_Final_Artwork_Advanced_Framework/blob/main/Coding2_The_FACE_WEB_Project/THE_FACE_WEB.pdf

----------------------
## Reference:
[https://numpy.org/](https://numpy.org/)

[https://python.plainenglish.io/face-mesh-detection-with-python-and-opencv-complete-project-359d81d6a712](https://python.plainenglish.io/face-mesh-detection-with-python-and-opencv-complete-project-359d81d6a712)

[https://streamlit.io/](https://streamlit.io/)

[https://www.python.org/](https://www.python.org/)

[https://pytorch.org/](https://pytorch.org/)

[https://mediapipe.dev/](https://mediapipe.dev/)

[https://docs.python.org/3/library/tempfile.html](https://docs.python.org/3/library/tempfile.html)

[https://www.youtube.com/watch?v=-IM3531b1XU&t=565s](https://www.youtube.com/watch?v=-IM3531b1XU&t=565s)

[https://docs.streamlit.io/knowledge-base/deploy/remote-start](https://docs.streamlit.io/knowledge-base/deploy/remote-start)
