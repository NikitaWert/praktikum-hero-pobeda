#!/usr/bin/env python
# coding: utf-8

# In[ ]:


#!/usr/bin/python
# -*- coding: utf-8 -*-

# импортируем библиотеки

# Построение графиков dash
import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output

# Работа с датой
from datetime import datetime 
import datetime as dt


# Построение графиков
from plotly import graph_objects as go
import matplotlib.pyplot as plt

# Работа с данными
#import numpy as np
import pandas as pd

# Работа с json
import json
# In[ ]:


# Загрузка датафрейма
pet_data = pd.read_csv('table.csv', encoding = 'cp1251')


# In[ ]:


# Переименовываю столбцы
pet_data.columns = ['id', 'shelter', 'purchase_date', 'service', 'price']


# In[ ]:


# Привожу дату в формат datetime
pet_data['purchase_date']  = pd.to_datetime(pet_data['purchase_date'], format = "%Y-%m-%d")

# Добавляю столбцы лет
pet_data['year'] = pet_data['purchase_date'].dt.year

# Месяцев
pet_data['month'] = pet_data['purchase_date'].dt.month
# Дней недели
pet_data['week'] = pet_data['purchase_date'].dt.week
# Дней
pet_data['day'] = pet_data['purchase_date'].dt.day

# Часов
pet_data['hour'] = pet_data['purchase_date'].dt.hour


# даты
pet_data['date'] = pet_data['purchase_date'].astype('datetime64[D]')

pet_data['month_date'] = pet_data['purchase_date'].astype('datetime64[M]')


# In[ ]:


# Заменяю "ё" на "е" привожу в нижний регистр
pet_data['service'] = pet_data['service'].str.lower().str.replace('ё','е').str.strip()
# Удаляю 1 с пробелом
pet_data.service=pet_data.service.str.replace('1 ', '')


# In[ ]:


# Создаем фильтр для кото- и песо- услуг
cat = ['котодень','котонеделя','котомесяц']
dog = ['песодень','песонеделя', 'песомесяц']
alls = cat+dog


# In[ ]:


# Делаем срез по услугам
pet_data_cat_dog = pet_data.copy()


# Передаем файлы Андрею
pet_data_cat_dog.to_json(orient='records',path_or_buf='out_teddy_json')
top_pet_shelter_a = pet_data_cat_dog.groupby('shelter')['price'].agg('sum').sort_values(ascending = False).reset_index()
top_pet_shelter_a['percent'] = round(top_pet_shelter_a['price']/(top_pet_shelter_a['price'].sum())*100,3)
top_pet_shelter_a.to_json(orient='records',path_or_buf='revenue_shelter_json')
top_pet_date = pet_data_cat_dog.groupby('date')['price'].agg('sum').reset_index()
top_pet_date.to_json(orient='records',path_or_buf='revenue_date_json')



# Строим дашборд


# In[ ]:


# Общее описание дашборда

note = '''
          Этот дашборд показывает историю взносов в приюты сервиса Teddy Food по кото- и песо- услугам. 
          Пожалуйста выбирите приют, услугу и период времени (начало, конец).
          
       '''


# In[ ]:


# Создаем лейаут запрос


external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']
app = dash.Dash(__name__, external_stylesheets=external_stylesheets,compress=False)
app.layout = html.Div(children=[  
    
    # формируем html
    html.H1(children =  'Доходы сервиса Teddy Food'),

    html.Br(),  

    # пояснения
    html.Label(note),

    html.Br(),
    
    html.Div([
        html.Div([

                        
            #html.Br(),
            # фильтр выбора по приюту
            html.Label('Фильтр по приюту:'),
            dcc.Dropdown(options = [{'label': x, 'value': x} for x in pet_data_cat_dog['shelter'].unique()], 
            value = pet_data_cat_dog['shelter'].unique().tolist(), 
            multi = True, id = 'shelter_dropdown'),


            
            #html.Br(),
            html.Br(),
            html.Label('Круговая диаграмма расределения доходов по приютам:'),

            dcc.Graph(
                style = {'height': '25vw'}, 
                id = 'pie_visits' # уникален для всех
            ), 
            # график  доходов по приютам
            html.Label('Доходы по приютам:'),

            dcc.Graph(
                style = {'height': '25vw'}, 
                id = 'time_revenue_graf'
            ),  
            
                                       

        ], className = 'eight columns'),
        
        html.Div([

            #html.Br(),

                        
            #html.Br(),
            # выбор временного периода
            html.Label('Фильтр даты:'),
            dcc.DatePickerRange(
            start_date = pet_data_cat_dog['date'].dt.date.min(),

            end_date = pet_data_cat_dog['date'].dt.date.max(),
                
            display_format = 'YYYY-MM-DD',
            id = 'dt_selector',      
                                ),


            # выбор по услуге
            html.Label('Фильтр по услуге:'),
            dcc.Dropdown(options = [{'label': x, 'value': x} for x in pet_data_cat_dog['service'].unique()], 
            value = pet_data_cat_dog['service'].unique().tolist(), 
            multi = True, id = 'service_dropdown'),          


            # график доходов по услугам за период
            html.Label('Доходы по услугам за период:'), 
            
            dcc.Graph(
                style = {'height': '25vw'}, 
                id = 'shelter_revenue_graph' 
            ), 
            # Sticky factor:
            html.Label('Sticky factor:'),

            dcc.Graph(
                style = {'height': '25vw'}, 
                id = 'sticky_graph'
            ),                           

        ], className = 'four columns'),

    ], className = 'row'),
])


# In[ ]:


# Описываем логику дашборда

@app.callback([Output('pie_visits', 'figure'),
               Output('shelter_revenue_graph', 'figure'),
               Output('time_revenue_graf', 'figure'),
               Output('sticky_graph', 'figure')
              ],
              [ Input('service_dropdown', 'value'),
                 Input('shelter_dropdown', 'value'),      
                 Input('dt_selector', 'start_date'),
                 Input('dt_selector', 'end_date')   
                ])
# Функция автоматического обновления данных
def update_figures(selected_service, selected_shelter, start_date, end_date):
    
    # Форматируем даты
    start_date = datetime.strptime(start_date, '%Y-%m-%d')
    end_date = datetime.strptime(end_date, '%Y-%m-%d')
  
   
    
    # Формируем запрос для фильтрации
    query = 'service.isin(@selected_service) and date >= @start_date and date <= @end_date and shelter.isin(@selected_shelter)'

    filter_dash_diagram = pet_data_cat_dog.query(query)
    
    top_pet_shelter = filter_dash_diagram.groupby('shelter')['price'].agg('sum').sort_values(ascending = True)
    #data = transfer_down(top_pet_shelter, 'shelter')
    #data = data.reset_index()
    
    name_rest = list(top_pet_shelter.index)
    values = top_pet_shelter
    #data = transfer_down(top_pet_shelter, 'shelter')
    data = top_pet_shelter.reset_index()

    # Круговая диаграмма
    # Первый график первого блока
    pie = [go.Pie(labels=name_rest, values=values, 
                             title = 'Распределение взносов между приютами')]
    
    # Второй график первого блока
    # Доходы по услугам за период времени
    top_pet_date = filter_dash_diagram.groupby('date')['price'].agg('sum').reset_index()
    
    bar_one = [go.Bar(x=top_pet_date['date'], y=top_pet_date['price'])]
    
    # Первый график второго блока
    # Доходы по приютам
    bar_two = []
    
    for shelter in data['shelter']:
        bar_two += [go.Bar(y = data.query('shelter == @shelter')['shelter'],
                 x = data.query('shelter == @shelter')['price'],
                             name = '', 
                    text= data.query('shelter == @shelter')['price'],
                            textposition='auto',orientation='h')]
    
    
    
    
    # Второй график второго блока
    # sticky factor
    dau_total = filter_dash_diagram.groupby('date').agg({'id': 'nunique'}).median()
    mau_total = filter_dash_diagram.groupby('month_date').agg({'id': 'nunique'}).median()
    wau_total = filter_dash_diagram.groupby(['year','week']).agg({'id': 'nunique'}).median()
    # Для DAU/WAU
    sticky_factor_week = round(dau_total/wau_total*100,3)
    # Для DAU/MAU
    sticky_factor_month = round(dau_total/mau_total*100,3)

    

    bar_three = []
    
    
    bar_three += [go.Bar(x = ['DAU/WAU %'],
                             y = [sticky_factor_week.iloc[0]],
                             name = 'DAU/WAU %', 
                             text= sticky_factor_week.iloc[0],
                             textposition='auto'
                            )
                     ]
    bar_three += [go.Bar(x = ['DAU/MAU %'],
                             y = [sticky_factor_month.iloc[0]],
                             name = 'DAU/MAU %', 
                             text= sticky_factor_month.iloc[0],
                             textposition='auto'
                            )
                     ]
    
    
   
    return (
            { # Первый график первого блока
             'data':  pie,
                 'layout':go.Layout(title_text='Соотношение доходов по приютам')
             
            },
            
            { # Второй график первогоы блока
            'data':bar_one,
            'layout':go.Layout(xaxis = {'title': 'Время'},
                               yaxis = {'title': 'Доход'},
                title_text='Доходы по услугам за период'
            )
            },

            # Первый график второго блока
            {'data':bar_two,
            'layout':go.Layout(xaxis = {'title': 'Доход'},
                               title_text= 'Распределение доходов по приютам'
            
            )
            },





                         
            # Второй график второго блока
            {'data':bar_three,
            'layout':go.Layout(xaxis = {'title': 'Показатель'},
                               yaxis = {'title': 'Процент'},
                title_text= 'Sticky factor'
            )
            }
    )
    

# Запуск серевера
if __name__ == '__main__':
    app.run_server(debug = True, host = '127.0.0.1')


# In[ ]:




