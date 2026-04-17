# Fast Fourier Transform (FFT) — An Informative Overview

## 1. Continuous Fourier Transform

The Fourier Transform decomposes a function into a continuous spectrum of frequencies.

For a function $f(t)$, the Fourier transform is:

$$\hat{f}(\omega) = \int_{-\infty}^{\infty} f(t)\, e^{-i \omega t} \, dt$$

and the inverse transform:

$$f(t) = \frac{1}{2\pi} \int_{-\infty}^{\infty} \hat{f}(\omega)\, e^{i \omega t} \, d\omega$$

These exponentials form an orthogonal basis for representing signals.

## 2. The Discrete Fourier Transform (DFT)

Obviously, computers cannot handle continuous signals, so we sample the function at discrete points.

The DFT converts a finite sequence of samples into frequency components:

$$X_k = \sum_{n=0}^{N-1} x_n \, e^{-2\pi i kn / N}, \quad k = 0, \dots, N-1$$

Inverse DFT:

$$x_n = \frac{1}{N} \sum_{k=0}^{N-1} X_k \, e^{2\pi i kn / N}$$

### Matrix Form

Let:

$$\omega_N = e^{-2\pi i / N}$$

Then:

$$X_k = \sum_{n=0}^{N-1} x_n \, \omega_N^{kn}$$

This can be written as:

$$\mathbf{X} = W_N \mathbf{x}$$

where $W_N$ is the Fourier matrix:

$$(W_N)_{k,n} = \omega_N^{kn}$$

## 3. Fast Fourier Transform (FFT)

The FFT reduces the complexity of the DFT using divide-and-conquer. The key insight is to exploit the symmetry of the roots of unity.
Split the sequence into:

- Even indices: $x_{2m}$
- Odd indices: $x_{2m+1}$

Then:

$$X_k=\sum_{m=0}^{N/2-1} x_{2m} e^{-2\pi i k(2m)/N}+\sum_{m=0}^{N/2-1} x_{2m+1} e^{-2\pi i k(2m+1)/N}$$

Factorizing:

$$X_k = E_k + \omega_N^k O_k$$

where:

- $E_k$: DFT of even-indexed terms  
- $O_k$: DFT of odd-indexed terms  
- $\omega_N^k = e^{-2\pi i k / N}$: Twiddle factor

Also:

$$X_{k + N/2} = E_k - \omega_N^k O_k$$

### Recursive Structure

Each DFT of size $N$ is reduced to two DFTs of size $N/2$:

$$N \rightarrow N/2 \rightarrow N/4 \rightarrow \cdots \rightarrow 1$$

This recursion continues until trivial DFTs of size 1.

## 4. Butterfly Operation

The fundamental computation unit of FFT is the **butterfly**:

$$\begin{cases}
X_k = E_k + W O_k \\
X_{k+N/2} = E_k - W O_k
\end{cases}
$$

where:

$$W = e^{-2\pi i k / N}$$

This combines two inputs into two outputs using one complex multiplication and two additions.

## 5. Bit-Reversal Permutation

## 6. Why FFT Works

The efficiency comes from key algebraic properties:

### Periodicity

$$
\omega_N^{k+N} = \omega_N^k
$$

### Symmetry

$$
\omega_N^{k + N/2} = -\omega_N^k
$$

### Matrix Factorization

The Fourier matrix can be decomposed into smaller Fourier transforms:

$$
W_N =
\begin{bmatrix}
I & D \\
I & -D
\end{bmatrix}
\begin{bmatrix}
W_{N/2} & 0 \\
0 & W_{N/2}
\end{bmatrix}
P
$$

where:

- $D$: diagonal matrix of twiddle factors  
- $P$: permutation matrix  
This structure enables divide-and-conquer computation.
