from django.db import models
from .models import *
import re
class pagination:

    paginate_by = 5
    buttons_show=5
    def paginate(self, objects_list, request=str):
        if self.paginate_by > objects_list.count():
            return objects_list, {}
        request = re.sub(r'^[^\d]*', '', request)

        if request == '':
             request = 1 
        if int(request) == 0:
            request = 1 
        left_border = int(request)*self.paginate_by - self.paginate_by
        right_border = int(request)*self.paginate_by

        page_buttons_text=[]

        
        max_button =  int(objects_list.count() / self.paginate_by)

        if int(request) <= 3:
            page_buttons_text.clear()
            page_buttons_text = []
            page_buttons_text.extend(range(2, self.buttons_show))
            page_buttons_text.extend(['...', max_button])
            return  objects_list[ left_border : right_border], page_buttons_text
        
        if max_button <= self.buttons_show :
            return objects_list[ left_border : right_border], range(max_button)
        if int(request)+ int(self.buttons_show/2) >= max_button:
            page_buttons_text = ['...']
            page_buttons_text.extend([ i for i in range(max_button-self.buttons_show+1 , max_button+1)])
            return  objects_list[ left_border : right_border], page_buttons_text
        else :
            page_buttons_text.extend( [ i for i  in range(int(request)- int(self.buttons_show/2) +1, int(request)+ int(self.buttons_show/2 )+1) ] )
        if int(request) - int(self.buttons_show/2) >= 2:
            tmp = ['...']
            tmp.extend(page_buttons_text)
            page_buttons_text =tmp
        page_buttons_text.extend(['...', max_button])
        
        return  objects_list[ left_border : right_border], page_buttons_text


        
def CreateFakePost():
    u = Author.objects.all()[0]
    tg = tag.objects.all()[0]
    p = post(text = 'Lorem', header= 'lorem', author = u)
    p.save()