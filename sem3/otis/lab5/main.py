import tkinter as tk
from tkinter import ttk
import numpy as np

class PairwiseComparisonApp:
    def __init__(self, parent):
        self.parent = parent
        self.frame = ttk.Frame(self.parent)
        self.frame.pack(fill='both', expand=True)
        self.alternatives = []
        self.create_widgets()
    
    def create_widgets(self):
        ttk.Label(self.frame, text="Количество альтернатив:").pack()
        self.num_alternatives = tk.StringVar(value="3")
        ttk.Entry(self.frame, textvariable=self.num_alternatives, width=10).pack()
        ttk.Button(self.frame, text="Создать матрицу", command=self.create_matrix).pack()
        
        self.alt_frame = ttk.Frame(self.frame)
        self.alt_frame.pack()
        
        self.matrix_frame = ttk.Frame(self.frame)
        self.matrix_frame.pack()
        
        self.result_frame = ttk.Frame(self.frame)
        self.result_frame.pack()
        
        ttk.Button(self.frame, text="Рассчитать", command=self.calculate).pack()
    
    def create_matrix(self):
        n = int(self.num_alternatives.get())
        
        for widget in self.alt_frame.winfo_children(): widget.destroy()
        for widget in self.matrix_frame.winfo_children(): widget.destroy()
        
        self.alt_entries = []
        for i in range(n):
            ttk.Label(self.alt_frame, text=f"Z{i+1}:").grid(row=i, column=0)
            entry = ttk.Entry(self.alt_frame, width=15)
            entry.grid(row=i, column=1)
            entry.insert(0, f"Альтернатива {i+1}")
            self.alt_entries.append(entry)
        
        self.matrix_vars = []
        for i in range(n):
            row_vars = []
            for j in range(n):
                if i == j:
                    var = tk.StringVar(value="0")
                    ttk.Label(self.matrix_frame, text="0").grid(row=i+1, column=j+1)
                else:
                    var = tk.StringVar(value="0")
                    ttk.Entry(self.matrix_frame, textvariable=var, width=3).grid(row=i+1, column=j+1)
                row_vars.append(var)
            self.matrix_vars.append(row_vars)
        
        for i in range(n):
            ttk.Label(self.matrix_frame, text=f"Z{i+1}").grid(row=i+1, column=0)
            ttk.Label(self.matrix_frame, text=f"Z{i+1}").grid(row=0, column=i+1)
    
    def calculate(self):
        n = int(self.num_alternatives.get())
        alternatives = [entry.get() for entry in self.alt_entries]
        
        matrix = np.zeros((n, n))
        for i in range(n):
            for j in range(n):
                if i != j:
                    matrix[i][j] = int(self.matrix_vars[i][j].get())
        
        prices = np.sum(matrix, axis=1)
        total_price = np.sum(prices)
        weights = prices / total_price if total_price > 0 else np.ones(n) / n
        
        self.show_results(alternatives, prices, weights)
    
    def show_results(self, alternatives, prices, weights):
        for widget in self.result_frame.winfo_children(): widget.destroy()
        
        tree = ttk.Treeview(self.result_frame, columns=('Alternative', 'Price', 'Weight', 'Rank'), show='headings')
        tree.heading('Alternative', text='Альтернатива')
        tree.heading('Price', text='Цена')
        tree.heading('Weight', text='Вес')
        tree.heading('Rank', text='Ранг')
        
        sorted_indices = np.argsort(weights)[::-1]
        for idx in sorted_indices:
            tree.insert('', 'end', values=(
                alternatives[idx],
                f"{prices[idx]:.0f}",
                f"{weights[idx]:.3f}",
                f"{sorted_indices.tolist().index(idx) + 1}"
            ))
        
        tree.pack()
        
        best_idx = sorted_indices[0]
        ttk.Label(self.result_frame, text=f"Лучшая: {alternatives[best_idx]} (вес: {weights[best_idx]:.3f})").pack()

class SequentialComparisonApp:
    def __init__(self, parent):
        self.parent = parent
        self.frame = ttk.Frame(self.parent)
        self.frame.pack(fill='both', expand=True)
        self.alternatives = []
        self.create_widgets()
    
    def create_widgets(self):
        ttk.Label(self.frame, text="Количество альтернатив:").pack()
        self.num_alternatives = tk.StringVar(value="4")
        ttk.Entry(self.frame, textvariable=self.num_alternatives, width=10).pack()
        ttk.Button(self.frame, text="Создать форму", command=self.create_form).pack()
        
        self.alt_frame = ttk.Frame(self.frame)
        self.alt_frame.pack()
        
        self.comp_frame = ttk.Frame(self.frame)
        self.comp_frame.pack()
        
        self.result_frame = ttk.Frame(self.frame)
        self.result_frame.pack()
        
        ttk.Button(self.frame, text="Рассчитать", command=self.calculate).pack()
    
    def create_form(self):
        n = int(self.num_alternatives.get())
        
        for widget in self.alt_frame.winfo_children(): widget.destroy()
        for widget in self.comp_frame.winfo_children(): widget.destroy()
        
        self.alt_entries = []
        self.initial_score_entries = []
        self.adjusted_score_entries = []
        
        for i in range(n):
            alt_entry = ttk.Entry(self.alt_frame, width=15)
            alt_entry.grid(row=i, column=0)
            alt_entry.insert(0, f"Z{i+1}")
            self.alt_entries.append(alt_entry)
            
            initial_entry = ttk.Entry(self.alt_frame, width=10)
            initial_entry.grid(row=i, column=1)
            initial_entry.insert(0, str(100 - i*20))
            self.initial_score_entries.append(initial_entry)
            
            adjusted_entry = ttk.Entry(self.alt_frame, width=10)
            adjusted_entry.grid(row=i, column=2)
            adjusted_entry.insert(0, str(100 - i*20))
            self.adjusted_score_entries.append(adjusted_entry)
        
        self.comparison_vars = []
        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    var = tk.StringVar(value="1")
                    ttk.Radiobutton(self.comp_frame, text=f"Z{i+1} > (Z{j+1}+Z{k+1})", 
                                   variable=var, value="1").pack()
                    ttk.Radiobutton(self.comp_frame, text=f"Z{i+1} < (Z{j+1}+Z{k+1})", 
                                   variable=var, value="0").pack()
                    self.comparison_vars.append((i, j, k, var))
    
    def calculate(self):
        n = int(self.num_alternatives.get())
        alternatives = [entry.get() for entry in self.alt_entries]
        
        adjusted_scores = [float(entry.get()) for entry in self.adjusted_score_entries]
        
        for i, j, k, var in self.comparison_vars:
            if int(var.get()) == 1:
                if adjusted_scores[i] <= adjusted_scores[j] + adjusted_scores[k]:
                    adjusted_scores[i] = adjusted_scores[j] + adjusted_scores[k] + 1
        
        for idx, score in enumerate(adjusted_scores):
            self.adjusted_score_entries[idx].delete(0, tk.END)
            self.adjusted_score_entries[idx].insert(0, str(int(score)))
        
        total_score = sum(adjusted_scores)
        weights = [score / total_score for score in adjusted_scores]
        
        self.show_results(alternatives, adjusted_scores, weights)
    
    def show_results(self, alternatives, scores, weights):
        for widget in self.result_frame.winfo_children(): widget.destroy()
        
        tree = ttk.Treeview(self.result_frame, columns=('Alternative', 'Score', 'Weight', 'Rank'), show='headings')
        tree.heading('Alternative', text='Альтернатива')
        tree.heading('Score', text='Оценка')
        tree.heading('Weight', text='Вес')
        tree.heading('Rank', text='Ранг')
        
        sorted_indices = sorted(range(len(weights)), key=lambda i: weights[i], reverse=True)
        for idx in sorted_indices:
            tree.insert('', 'end', values=(
                alternatives[idx],
                f"{scores[idx]:.0f}",
                f"{weights[idx]:.3f}",
                f"{sorted_indices.index(idx) + 1}"
            ))
        
        tree.pack()
        
        best_idx = sorted_indices[0]
        ttk.Label(self.result_frame, text=f"Лучшая: {alternatives[best_idx]} (вес: {weights[best_idx]:.3f})").pack()

class MainApplication:
    def __init__(self, root):
        self.root = root
        self.root.title("Методы экспертных оценок")
        self.root.geometry("700x600")
        
        notebook = ttk.Notebook(root)
        
        pair_frame = ttk.Frame(notebook)
        notebook.add(pair_frame, text="Парные сравнения")
        PairwiseComparisonApp(pair_frame)
        
        seq_frame = ttk.Frame(notebook)
        notebook.add(seq_frame, text="Последовательные сравнения")
        SequentialComparisonApp(seq_frame)
        
        notebook.pack(expand=1, fill='both')

def main():
    root = tk.Tk()
    MainApplication(root)
    root.mainloop()

if __name__ == "__main__":
    main()